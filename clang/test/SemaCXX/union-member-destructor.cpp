// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

template <class T> struct VSX {
  ~VSX() { static_assert(sizeof(T) != 4, ""); } // expected-error {{static assertion failed due to requirement 'sizeof(int) != 4':}} \
                                                // expected-note {{expression evaluates to '4 != 4'}}
};
struct VS {
  union {
    VSX<int> _Tail;
  };
  ~VS() { }
  VS(short);
};
VS::VS(short) : _Tail() { } // expected-note {{in instantiation of member function 'VSX<int>::~VSX' requested here}}
