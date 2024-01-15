use stack_proj::funcs;

#[test]
fn valide_without_brackets() { assert_eq!(funcs::is_valide_brackets("aa"), true) }

#[test]
fn valide_with_one_brackets() { assert_eq!(funcs::is_valide_brackets("{}"), true) }

#[test]
fn valide_with_lot_brackets() { assert_eq!(funcs::is_valide_brackets("{[(<>)]}"), true) }

#[test]
fn invalide_with_unopened_bracket() { assert_eq!(funcs::is_valide_brackets("}"), false) }

#[test]
fn invalide_with_unclosed_bracket() { assert_eq!(funcs::is_valide_brackets("{"), false) }

#[test]
fn invalide_with_one_brackets() { assert_eq!(funcs::is_valide_brackets("{)"), false) }

#[test]
fn invalide_with_lot_brackets() { assert_eq!(funcs::is_valide_brackets("{{<})"), false) }