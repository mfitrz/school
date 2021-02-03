#include <gtest/gtest.h>
#include <string>
#include "dna.h"

TEST(dna, constructor) {
    dna d;
    EXPECT_EQ(d.size(), 2);
    EXPECT_EQ(d.toString(), "XX");
    for (int i = 0; i < d.size(); i++) {
        EXPECT_EQ(d.at(i), 'X');
    }
    EXPECT_EQ(d.toString(), "XX");
    EXPECT_EQ(d.isLinked(), true);
    for (int i = 0; i < d.size(); i++) {
        d.at(i) = 'A';
        EXPECT_EQ(d.at(i), 'A');
    }
    EXPECT_EQ(d.toString(), "AA");
    for (int i = 0; i < 100; i++) {
        dna b;
        EXPECT_EQ(b.size(), 2);
        EXPECT_EQ(b.toString(), "XX");
    }
}

TEST(dna, secondConstructor) {
    string dnastr = "AGATC";
    dna d(dnastr);
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), dnastr);
    EXPECT_EQ(d.size(), dnastr.length());
    string yes = "";
    dna a(yes);
    EXPECT_EQ(a.isLinked(), true);
    EXPECT_EQ(a.toString(), yes);
    EXPECT_EQ(a.size(), yes.length());
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna l(hi);
        EXPECT_EQ(l.size(), i);
        EXPECT_EQ(l.isLinked(), true);
        EXPECT_EQ(l.toString(), hi);
        hi += "1";
    }
}

TEST(dna, size) {
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna d(hi);
        EXPECT_EQ(d.size(), i);
        EXPECT_EQ(d.isLinked(), true);
        EXPECT_EQ(d.toString(), hi);
        hi += "O";
    }
}

TEST(dna, toString) {
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna d(hi);
        EXPECT_EQ(d.size(), i);
        EXPECT_EQ(d.isLinked(), true);
        EXPECT_EQ(d.toString(), hi);
        hi += "A";
    }
}

TEST(dna, at) {
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna d(hi);
        EXPECT_EQ(d.size(), i);
        EXPECT_EQ(d.isLinked(), true);
        EXPECT_EQ(d.toString(), hi);
        hi += "A";
    }
     dna b(hi);
     for (int i = 99; i >= 0; i--) {
        b.at(i) = 'B';
        EXPECT_EQ(b.isLinked(), true);
        EXPECT_EQ(b.size(), 100);
        EXPECT_EQ(b.at(i), 'B');
    }
}


TEST(dna, clear) {
    string dnastr = "AGATC";
    dna d(dnastr);
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), dnastr);
    EXPECT_EQ(d.size(), dnastr.length());
    d.clear();
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), "");
    EXPECT_EQ(d.size(), 0);
    string yes = "";
    dna a(yes);
    EXPECT_EQ(a.isLinked(), true);
    EXPECT_EQ(a.toString(), yes);
    EXPECT_EQ(a.size(), yes.length());
    a.clear();
    EXPECT_EQ(a.isLinked(), true);
    EXPECT_EQ(a.toString(), yes);
    EXPECT_EQ(a.size(), yes.length());
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna g(hi);
        EXPECT_EQ(g.size(), i);
        EXPECT_EQ(g.isLinked(), true);
        EXPECT_EQ(g.toString(), hi);
        hi += "A";
    }
     for (int i = 99; i >= 0; i--) {
        dna b(hi);
        b.at(i) = 'B';
        EXPECT_EQ(b.isLinked(), true);
        EXPECT_EQ(b.size(), 100);
        EXPECT_EQ(b.at(i), 'B');
        b.clear();
        EXPECT_EQ(b.size(), 0);
        EXPECT_EQ(b.isLinked(), true);
    }
}

TEST(dna, copyConstructor) {
    string yes = "Hello";
    dna d(yes);
    dna b(d);
    EXPECT_EQ(b.isLinked(), true);
    EXPECT_EQ(b.toString(), yes);
    EXPECT_EQ(b.size(), yes.length());
    EXPECT_EQ(d == b, true);
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna a(hi);
        dna c(a);
        EXPECT_EQ(c.isLinked(), true);
        EXPECT_EQ(c.toString(), hi);
        EXPECT_EQ(c.size(), hi.length());
        EXPECT_EQ(c == a, true);
        hi += "A";
    }
}

TEST(dna, equalsOperator) {
    string yes = "Hello";
    dna d;
    dna b(yes);
    d = b;
    EXPECT_EQ(d == b, true);
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), yes);
    EXPECT_EQ(d.size(), yes.length());
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna a(hi);
        dna c;
        c = a;
        EXPECT_EQ(c.isLinked(), true);
        EXPECT_EQ(c.toString(), hi);
        EXPECT_EQ(c.size(), hi.length());
        EXPECT_EQ(c == a, true);
        hi += "A";
    }
}

TEST(dna, operatorEquality) {
    dna d;
    EXPECT_EQ(d.size(), 2);
    EXPECT_EQ(d.toString(), "XX");
    for (int i = 0; i < d.size(); i++) {
        EXPECT_EQ(d.at(i), 'X');
    }
    EXPECT_EQ(d.toString(), "XX");
    EXPECT_EQ(d.isLinked(), true);
    dna a("XX");
    EXPECT_EQ(d == a, true);
    string dnastr = "AGATC";
    dna c(dnastr);
    dna x(dnastr);
    dna e("HI");
    dna f("AGGTC");
    dna b("");
    EXPECT_EQ(c.isLinked(), true);
    EXPECT_EQ(c.toString(), dnastr);
    EXPECT_EQ(c.size(), dnastr.length());
    EXPECT_EQ(c == x, true);
    EXPECT_EQ(c == e, false);
    EXPECT_EQ(c == f, false);
    EXPECT_EQ(c == b, false);
    c.clear();
    EXPECT_EQ(c.isLinked(), true);
    EXPECT_EQ(c.toString(), "");
    EXPECT_EQ(c.size(), 0);
    EXPECT_EQ(c == b, true);
    string hi = "";
    for (int i = 0; i < 100; i++) {
        dna a(hi);
        dna c;
        c = a;
        EXPECT_EQ(c.isLinked(), true);
        EXPECT_EQ(c.toString(), hi);
        EXPECT_EQ(c.size(), hi.length());
        EXPECT_EQ(c == a, true);
        hi += "A";
    }
}

TEST(dna, splice) {
    dna d("AGATC");
    dna a("GAT");
    EXPECT_EQ(d.splice(a), true);
    EXPECT_EQ(d.toString(), "AC");
    EXPECT_EQ(d.isLinked(), true);
    dna b("GTCAGTCAGT");
    dna c("CAG");
    dna e("TAG");
    dna f("GTCAGTCAGT");
    EXPECT_EQ(b.splice(c), true);
    EXPECT_EQ(b.toString(), "GTTCAGT");
    EXPECT_EQ(b.isLinked(), true);
    EXPECT_EQ(f.splice(e), false);
    EXPECT_EQ(f.toString(), "GTCAGTCAGT");
    EXPECT_EQ(f.isLinked(), true);
    dna g("CATMAT");
    dna h("CAT");
    dna m("MAT");
    dna z("MADHAT");
    dna x("HAT");
    EXPECT_EQ(g.splice(h), true);
    EXPECT_EQ(g.toString(), "MAT");
    EXPECT_EQ(g.isLinked(), true);
    EXPECT_EQ(g.size(), 3);
    EXPECT_EQ(g.splice(m), true);
    EXPECT_EQ(g.toString(), "");
    EXPECT_EQ(g.isLinked(), true);
    EXPECT_EQ(g.size(), 0);
    EXPECT_EQ(z.splice(x), true);
    EXPECT_EQ(z.toString(), "MAD");
    EXPECT_EQ(z.isLinked(), true);
    EXPECT_EQ(z.size(), 3);
    dna p("AGAT");
    dna o("GAT");
    EXPECT_EQ(p.splice(o), true);
    EXPECT_EQ(p.toString(), "A");
    EXPECT_EQ(p.isLinked(), true);
    EXPECT_EQ(p.size(), 1);
    dna n("GATA");
    EXPECT_EQ(n.splice(o), true);
    EXPECT_EQ(n.toString(), "A");
    EXPECT_EQ(n.isLinked(), true);
    EXPECT_EQ(n.size(), 1);
    string hi = "";
    dna u;
    for (int i = 0; i < 100; i++) {
        dna xyz(hi);
        u = xyz;
        hi += "CAT";
    }
    while(u.size() != 0){
        EXPECT_EQ(u.splice(h), true);
        EXPECT_EQ(u.isLinked(), true);
    }
    dna yes("");
    EXPECT_EQ(yes.splice(h), false);
    EXPECT_EQ(yes.size(), 0);
    dna hello("ACATCAT");
    EXPECT_EQ(hello.splice(h), true);
    EXPECT_EQ(hello.toString(), "ACAT");
    EXPECT_EQ(hello.splice(h), true);
    EXPECT_EQ(hello.toString(), "A");
    dna yikes("CACATCAT");
    EXPECT_EQ(yikes.splice(h), true);
    EXPECT_EQ(yikes.toString(), "CACAT");
    EXPECT_EQ(yikes.size(), 5);
    EXPECT_EQ(yikes.splice(h), true);
    EXPECT_EQ(yikes.toString(), "CA");
    dna hello1("CCAT");
    EXPECT_EQ(hello1.splice(h), true);
    EXPECT_EQ(hello1.toString(), "C");
    dna hello2("CACCCAT");
    EXPECT_EQ(hello2.splice(h), true);
    EXPECT_EQ(hello2.toString(), "CACC");
    dna LMAO("AGAGATC");
    dna LMAO2("AGATC");
    EXPECT_EQ(LMAO.splice(LMAO2), true);
}
