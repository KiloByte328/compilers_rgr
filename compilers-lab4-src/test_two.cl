class Main {
    a() : Int {
        33
    };
    x : Int <- 22;
};

class Absurd {
    ret() : Int {
        42
    };
    ret() : Int {
        24
    };
    newID : Int <- 22;
    secondID : Int;
    thirdID : String;
    secondID : String;
    newStr() : String {
        "Hello\
        Again"
    };
    secondNewStr() : String {
        secondID <- 33
    };
    thirdNewStr(x : Int) : Int {
        x <- 21
    };
    fourthNewStr (newID : String) : String {
        "Someting String"
    };
};

class Something inherits Absurd {
    doSmth(i : Int) : Int {
        i / 2
    };
    dosmthwhile() : Int {
        while 1 loop 42 / 2 pool
    };
    newID : Int <- 21;
    fthr() : Int {
        3 + 5
    };
    newFeat() : String {
        2@Int.fun()
    };
};

class Absurd inherits Bruh {
    abs() : Int {
        32
    };
    nabs() : Int {
        1 + "Hello"
    };
};

class Absurd inherits Something {
    abs() : Int {
        32
    };
    nabs() : Int {
        1 + "Hello"
    };
};