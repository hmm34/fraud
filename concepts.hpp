
// Andrew Sutton

#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <type_traits>
#include <iosfwd>

// Is true if and only if T and U are the same type.
template<typename T, typename U>
  concept bool 
  Same() { return __is_same_as(T, U); }

// Is true if and only if T is derived from U or is the same as U.
template<typename T, typename U>
  concept bool 
  Derived() { return __is_base_of(U, T); }

// Is true if and only if T can be implicitly converted to U through
// a user-defined conversion sequence.
template<typename T, typename U>
  concept bool 
  Convertible() { return __is_convertible_to(T, U); }

// Represents the common type of a sequence of type arguments. More
// precisely, if there exists some type C such that each type T in Ts
// can be converted to C, then C is the common type of all T in Ts.
//
// There are two common uses of the Common_type facility: defining
// requirements on heterogeneously typed templates, and extracting a
// meaningful type for concept checking in the presence of perfect
// forwarding.
//
// Note that in cases where forwarding is used, the unary Common_type
// provides the type against which concept checking should be done.
// For example:
//
//      template<typename T>
//        requires<Object<Common_type<T>>()
//          void f(T&& x);
//
// The Common_type wil
template<typename... Ts>
  using Common_type = typename std::common_type<Ts...>::type;

// True if and only if there exists a common type of Ts.
template<typename... Ts>
  concept bool 
  Common() {
    return requires () { 
      Common_type<Ts...>; // FIXME: This better be a type requirement.
    }; 
  }


namespace impl {
template<typename... Args>
  struct are_same;

template<>
  struct are_same<> : std::true_type { };

template<typename T>
  struct are_same<T> : std::true_type { };

template<typename T, typename U, typename... Args>
  struct are_same<T, U, Args...> 
    : std::integral_constant<
        bool, 
        std::is_same<T, U>::value and are_same<U, Args...>::value
      >
  { };

} // namespace impl

// True when all types are the same.
template<typename... Args>
  concept bool 
  Homogeneous() { return impl::are_same<Args...>::value; }


// -------------------------------------------------------------------------- //
// Relational concepts

// Is true if and only if arguments of type T can be compared using the 
// `==` and `!=` operators.
//
// Types modeling this concept must ensure that the `==` operator
// returns true only when the arguments have the same value. 
template<typename T>
  concept bool 
  Equality_comparable() {
    return requires (T a, T b) {
             {a == b} -> bool;
             {a != b} -> bool;
           };
  }

// Is true if and only if arguments of types T and U share a common type
// and can be compared using the == and != operators.
//
// Pairs of types modeling this concept must ensure the `==` operator
// returns true only when the arguments, when converted to their common
// type, and those converted values are the same.
template<typename T, typename U>
  concept bool 
  Equality_comparable() {
    return Equality_comparable<T>() 
        && Equality_comparable<U>() 
        && requires (T t, T u) {
             {t == u} -> bool;
             {u == t} -> bool;
             {t != u} -> bool;
             {u != t} -> bool;
          };
  }

// Is true if and only if arguments of type T can be compared using the
// inequality operators `<`, `>`, `<=`, and `>=`.
//
// Types modeling this concept must ensure that the `<` operator defines
// a strict weak order.
template<typename T>
  concept bool 
  Weakly_ordered() {
    return requires (T a, T b) {
             {a < b} -> bool;
             {a > b} -> bool;
             {a <= b} -> bool;
             {a >= b} -> bool;
           };
  }

// Weakly ordered
template<typename T, typename U>
  concept bool Weakly_ordered() {
    return Weakly_ordered<T>() 
        && Weakly_ordered<U>() 
        && requires (T t, T u) {
             {t < u} -> bool;
             {u < t} -> bool;
             {t > u} -> bool;
             {u > t} -> bool;
             {t <= u} -> bool;
             {u <= t} -> bool;
             {t >= u} -> bool;
             {u <= t} -> bool;
      };
  }

// Totally ordered
template<typename T>
  concept bool Totally_ordered() {
    return Equality_comparable<T>() && Weakly_ordered<T>();
  }

// Totally ordered
template<typename T, typename U>
  concept bool Totally_ordered()
  {
    return Totally_ordered<T>() 
        && Totally_ordered<U>()
        && Equality_comparable<T, U>()
        && Weakly_ordered<T, U>();
  }


// -------------------------------------------------------------------------- //
// Construction and destruction

// Is true if a variable of type T can be destroyed.
template<typename T>
  concept bool 
  Destructible() { return std::is_destructible<T>::value; }

// Is true if and only if an object of type T can be constructed with
// the types of arguments in Args.
template<typename T, typename... Args>
  concept bool Constructible() {
    return Destructible<T>() && std::is_constructible<T, Args...>::value; 
  }

// Is true if and only if an object of T can be default constructed.
//
// Note that default construction implies that an object of type T can
// also be default initialized. Types modeling this concept must ensure
// that any two default initialized objects must have the same value.
template<typename T>
  concept bool 
  Default_constructible() { return Constructible<T>(); }

// Is true if and only if an object of type T can be move constructed.
template<typename T>
  concept bool 
  Move_constructible() { return Constructible<T, T&&>(); }

// Is true if and only if an object of type T can be copy constructed.
template<typename T>
  concept bool 
  Copy_constructible() {
    return Move_constructible<T>() && Constructible<T, const T&>(); 
  }

// Is true if and only if an argument of type T can be assigned a value
// of type U.
//
// Note that T is typically expected to be an lvalue reference type.
template<typename T, typename U>
  concept bool 
  Assignable() { return std::is_assignable<T, U>::value; }

// Is true if and only if an object of type T can be move assigned.
template<typename T>
  concept bool 
  Move_assignable() { return Assignable<T&, T&&>(); }

// Is true if and only if an object of type T can be copy assigned.
template<typename T>
  concept bool 
  Copy_assignable() {
    return Move_assignable<T>() && Assignable<T&, const T&>(); 
  }


// Is true if and only if T supports move semantics. The type T must
// be move constructible and move assignable.
template<typename T>
  concept bool 
  Movable() {
    return Move_constructible<T>() && Move_assignable<T>();
  }

// Is true if and only if T supports copy semantics. The type T must 
// be copy constructible and copy assignable. 
template<typename T>
  concept bool 
  Copyable() {
    return Copy_constructible<T>() && Copy_assignable<T>();
  }

// -------------------------------------------------------------------------- //
// Regular types

// Is true if and only if T is a semiregular type. A semiregular type
// is both default constructible and copyable.
template<typename T>
  concept bool 
  Semiregular() { return Default_constructible<T>() && Copyable<T>(); }

// Is true if T is a regular type. A regular type is a semiregular type
// that is also equality comparable.
template<typename T>
  concept bool 
  Regular() { return Semiregular<T>() && Equality_comparable<T>(); }

// Is true if T is an ordered type.
template<typename T>
  concept bool 
  Ordered() { return Regular<T>() && Totally_ordered<T>(); }


// -------------------------------------------------------------------------- //
// Abstractions
//
// FIXME: These are currently defined in terms of sets of fundamental types.
// It would be better if we defined them in terms of required operations
// and their associated semantics.

// True whenver T is a standard integral type.
template<typename T>
  concept bool 
  Integer() {
    return std::is_integral<T>::value;
  }

// True whenever T is a standard floating point type.
template<typename T>
  concept bool
  Real() {
    return std::is_floating_point<T>::value;
  }


// -------------------------------------------------------------------------- //
// Function types

// Function
template<typename F, typename... Args>
  concept bool 
  Function() {
    return Copy_constructible<F>()
        && requires (F f, Args... args) {
             f(args...);
           };
  }

template<typename F, typename... Args>
  concept bool 
  Homogeneous_function() {
    return Function<F, Args...>()
       and Homogeneous<Args...>();
  }

// Predicate
template<typename P, typename... Args>
  concept bool 
  Predicate() {
    return requires (P pred, Args... args) {
             {pred(args...)} -> bool;
           };
  }

template<typename P, typename... Args>
  concept bool
  Homogeneous_predicate() {
    return Predicate<P, Args...>
       and Homogeneous<Args...>();
  }

// Relation
template<typename R, typename T>
  concept bool 
  Relation() {
    return Predicate<R, T, T>();
  }

// Relation (cross-type)
template<typename R, typename T, typename U>
  concept bool 
  Relation() {
    return Relation<R, T>()
        && Relation<R, U>()
        && Common<T, U>()
        && requires (R r, T t, U u) {
             {r(t, u)} -> bool;
             {r(u, t)} -> bool;
           };
  }

template<typename F, typename... Args>
  concept bool
  Operation() {
    return Homogeneous<Args...>()
       and requires(F fn, Args... args) {
             {fn(args...)} -> Common_type<Args...>;
           };
  }

// Unary_operation
template<typename F, typename T>
  concept bool 
  Unary_operation() {
    return Operation<F, T>();
  }

// Binary_operation
//
// TODO: Provide a multi-argument version of this?
template<typename F, typename T>
  concept bool 
  Binary_operation() {
    return Operation<F, T, T>();
  }


namespace impl {
template<typename T>
  struct distance_type { using type = std::ptrdiff_t; };

template<typename T>
  requires requires() { typename T::distance_type; }
    struct distance_type<T> { using type = typename T::distance_type; };
} // namespace impl


// The distance type is defined for transforms. By default, it is
// the same as ptrdiff_t.
template<typename T>
  using Distance_type = typename impl::distance_type<T>::type;


// Transform
//
// Note that the requriement for Distance_type is unnecessary since it is
// defined for all types. However, the requirement is still written to
// explicitly denote the inclusion of that type in the interface of the
// concept.
template<typename F, typename T>
  concept bool 
  Transform() {
    return Unary_operation<F, T>()
       and requires () {
             Distance_type<F>;
           };
  }


// -------------------------------------------------------------------------- //
// Streamable types

// A type is input streamable if it can be extracted from a formatted
// input stream derived from std::istream.
template<typename T>
  concept bool
  Input_streamable() {
    return requires(std::istream& s, T x) {
      s >> x;
    };
  }

template<typename T>
  concept bool
  Output_streamable() {
    return requires(std::ostream& s, T x) {
      s << x;
    };
  }

template<typename T>
  concept bool
  Streamable() {
    return Input_streamable<T>() and Output_streamable<T>();
  }


// -------------------------------------------------------------------------- //
// Associated types

// Miscellaneous associated types

namespace impl {
// Strip references and qualifiers from T.
//
// TODO: Are there any other types that we can't allow to decay?
template<typename T>
  struct strip_refquals : std::decay<T> { };

template<typename T>
  struct strip_refquals<T[]> { using type = T[]; };

template<typename T, std::size_t N>
  struct strip_refquals<T[N]> { using type = T[N]; };

template<typename R, typename... Ts>
  struct strip_refquals<R(Ts...)> { using type = R(Ts...); };

template<typename T>
  using strip = typename strip_refquals<T>::type;
} // namespace impl

/// For any type T, returns a non-qualified, non-reference type U. This
/// facility is primarily intended to remove qualifiers and references
/// that appear in forwarded arguments.
template<typename T>
  using Strip = impl::strip<T>;


namespace impl {
template<typename T>
  struct get_value_type;

template<typename T>
  struct get_value_type<T*> { using type = T; };

template<typename T>
  struct get_value_type<const T*> { using type = T; };

template<typename T>
  struct get_value_type<T[]> { using type = T; };

template<typename T, std::size_t N>
  struct get_value_type<T[N]> { using type = T; };

template<typename T>
  requires requires () { typename T::value_type; }
    struct get_value_type<T> { using type = typename T::value_type; };

// Make iostreams have a value type.
template<typename T>
  requires Derived<T, std::ios_base>()
    struct get_value_type<T> { using type = typename T::char_type; };

template<typename T>
  using value_type = typename get_value_type<Strip<T>>::type;
} // namespace impl

// Value type
template<typename T>
  using Value_type = impl::value_type<T>;


namespace impl {
template<typename T>
  struct get_difference_type;

template<typename T>
  struct get_difference_type<T*> { using type = std::ptrdiff_t; };

template<typename T>
  struct get_difference_type<T[]> { using type = std::ptrdiff_t; };

template<typename T, std::size_t N>
  struct get_difference_type<T[N]> { using type = std::ptrdiff_t; };

template<typename T>
  requires requires () { typename T::difference_type; }
    struct get_difference_type<T> { using type = typename T::difference_type; };

template<typename T>
  using difference_type = typename get_difference_type<Strip<T>>::type;
} // namespace impl

// Difference_type
template<typename T>
  using Difference_type = impl::difference_type<T>;

namespace impl {
template<typename T>
  struct get_size_type;

template<typename T>
  struct get_size_type<T*> { using type = std::size_t; };

template<typename T>
  struct get_size_type<T[]> { using type = std::size_t; };

template<typename T, std::size_t N>
  struct get_size_type<T[N]> { using type = std::size_t; };

template<typename T>
  requires requires () { typename T::size_type; }
    struct get_size_type<T> { using type = typename T::size_type; };  

template<typename T>
  using size_type = typename get_size_type<Strip<T>>::type;
} // namespace impl

// Size_type
template<typename T>
  using Size_type = impl::size_type<T>;



// -------------------------------------------------------------------------- //
// Elements of Programming


#endif

