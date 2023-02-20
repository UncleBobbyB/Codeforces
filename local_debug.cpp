#include "localdebug.h"

template<typename a, typename b> 
static ostream& operator << (ostream &os, const pair<a, b> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template<typename t_container, typename t = typename enable_if<!is_same<t_container, string>::value, typename t_container::value_type>::type> 
static ostream& operator << (ostream &os, const t_container &v) { 
    os << '{';
    string sep; 
    for (const t &x : v) 
        os << sep << x, sep = ", "; 
    return os << '}'; 
}

void dbg_out() {
    cerr << endl; 
}

template<typename head, typename... tail> void dbg_out(head h, tail... t) {
    cerr << ' ' << h; dbg_out(t...);
}