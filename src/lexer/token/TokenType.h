#pragma once

namespace Lexing {

enum TokenType {
    eof = 0,
    identifier,
    literal,
    braceLeft,
    braceRight,
    bracketLeft,
    bracketRight,
    parenLeft,
    parenRight,
    diamondLeft,
    diamondRight,
    doubleQuote,
    singleQuote,
    comma,
    grave,
    fun,
    t_if,
    t_else,
    t_switch,
    t_case,
    t_break,
    t_continue,
    t_for,
    t_while,
    t_do,
    t_return,
    t_class,
    t_enum,
    t_private,
    t_public,
    t_protected,
    t_throw,
    t_try,
    t_catch,
    t_not,
    t_and,
    pipe,
    shLeft,
    shRight,
    plus,
    minus,
    times,
    divided,
    power,
    modulo,
    andAssign,
    pipeAssign,
    shLeftAssign,
    shRightAssign,
    plusAssign,
    minusAssign,
    timesAssign,
    dividedAssign,
    powerAssign,
    moduloAssign,
    lessEquals,
    greaterEquals,
    assign,
    equals,
    notEquals,
    arrow,
    questionMark,
    column,
    import,
    package,
    var,
    val,
    by,
    data,
    immutable,
    singleton,
    interface,
    sealed,
    open,
    abstract,
    internal,
    annotation,
    at,
    external,
    constructor,
    destructor,
    final,
    override,
    dot,

    // string stuff

    escSingleQuote,
    escDoubleQuite,
    escBackSlash,
    escNewLine,
    escCarriageReturn,
    escTab,
    escBackspace,
    escFormFeed,
    escBell,
    escOctal,
    escHex,
    escUnicode,
    escDollarSign,
    dollarSign,
};

}
