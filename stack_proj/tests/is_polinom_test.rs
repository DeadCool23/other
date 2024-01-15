use stack_proj::funcs;

#[test]
fn odd_len_polinom() { assert_eq!(funcs::is_polinom(454), true) }

#[test]
fn even_len_polinom() { assert_eq!(funcs::is_polinom(44), true) }

#[test]
fn odd_len_npolinom() { assert_eq!(funcs::is_polinom(453), false) }

#[test]
fn even_len_npolinom() { assert_eq!(funcs::is_polinom(43), false) }
