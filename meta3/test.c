int main(void) {
    int a = 1;
    char b = 'b';
    short c = 3;
    double d = 4.0;

    a = a & a | a ^ a && a * a / a - a % a + a;
    b = b & b | b ^ b && b * b / b - b % b + b;
    c = c & c | c ^ c && c * c / c - c % c + c;
    d = d & d | d ^ d && d * d / d - d % d + d;
    a = a & b | c ^ d && a * b / c - d % a + b;
    b = b & a | c ^ d && b * a / c - d % b + a;
    c = c & d | a ^ b && c * d / a - b % c + d;
    d = d & a | b ^ c && d * a / b - c % d + a;
    a = a & b | c ^ d && a * b / c - d % a + b;
    b = b & a | c ^ d && b * a / c - d % b + a;
    c = c & d | a ^ b && c * d / a - b % c + d;
    d = d & a | b ^ c && d * a / b - c % d + a;
    a& a;
    a& b;
    a& c;
    a& d;
    a | a;
    a | b;
    a | c;
    a | d;
    a ^ a;
    a ^ b;
    a ^ c;
    a ^ d;
    a&& a;
    a&& b;
    a&& c;
    a&& d;
    a* a;
    a* b;
    a* c;
    a* d;
    a / a;
    a / b;
    a / c;
    a / d;
    a - a;
    a - b;
    a - c;
    a - d;
    a % a;
    a % b;
    a % c;
    a % d;
    a + a;
    a + b;
    a + c;
    a + d;
    b& a;
    b& b;
    b& c;
    b& d;
    b | a;
    b | b;
    b | c;
    b | d;
    b ^ a;
    b ^ b;
    b ^ c;
    b ^ d;
    b&& a;
    b&& b;
    b&& c;
    b&& d;
    b* a;
    b* b;
    b* c;
    b* d;
    b / a;
    b / b;
    b / c;
    b / d;
    b - a;
    b - b;
    b - c;
    b - d;
    b % a;
    b % b;
    b % c;
    b % d;
    b + a;
    b + b;
    b + c;
    b + d;
    c& a;
    c& b;
    c& c;
    c& d;
    c | a;
    c | b;
    c | c;
    c | d;
    c ^ a;
    c ^ b;
    c ^ c;
    c ^ d;
    c&& a;
    c&& b;
    c&& c;
    c&& d;
    c* a;
    c* b;
    c* c;
    c* d;
    c / a;
    c / b;
    c / c;
    c / d;
    c - a;
    c - b;
    c - c;
    c - d;
    c % a;
    c % b;
    c % c;
    c % d;
    c + a;
    c + b;
    c + c;
    c + d;
    d& a;
    d& b;
    d& c;
    d& d;
    d | a;
    d | b;
    d | c;
    d | d;
    d ^ a;
    d ^ b;
    d ^ c;
    d ^ d;
    d&& a;
    d&& b;
    d&& c;
    d&& d;
    d* a;
    d* b;
    d* c;
    d* d;
    d / a;
    d / b;
    d / c;
    d / d;
    d - a;
    d - b;
    d - c;
    d - d;
    d % a;
    d % b;
    d % c;
    d % d;
    d + a;
    d + b;
    d + c;
    d + d;
    if (1) {
        a = a & a | a ^ a && a * a / a - a % a + a;
        b = b & b | b ^ b && b * b / b - b % b + b;
        c = c & c | c ^ c && c * c / c - c % c + c;
        d = d & d | d ^ d && d * d / d - d % d + d;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a& a;
        a& b;
        a& c;
        a& d;
        a | a;
        a | b;
        a | c;
        a | d;
        a ^ a;
        a ^ b;
        a ^ c;
        a ^ d;
        a&& a;
        a&& b;
        a&& c;
        a&& d;
        a* a;
        a* b;
        a* c;
        a* d;
        a / a;
        a / b;
        a / c;
        a / d;
        a - a;
        a - b;
        a - c;
        a - d;
        a % a;
        a % b;
        a % c;
        a % d;
        a + a;
        a + b;
        a + c;
        a + d;
        b& a;
        b& b;
        b& c;
        b& d;
        b | a;
        b | b;
        b | c;
        b | d;
        b ^ a;
        b ^ b;
        b ^ c;
        b ^ d;
        b&& a;
        b&& b;
        b&& c;
        b&& d;
        b* a;
        b* b;
        b* c;
        b* d;
        b / a;
        b / b;
        b / c;
        b / d;
        b - a;
        b - b;
        b - c;
        b - d;
        b % a;
        b % b;
        b % c;
        b % d;
        b + a;
        b + b;
        b + c;
        b + d;
        c& a;
        c& b;
        c& c;
        c& d;
        c | a;
        c | b;
        c | c;
        c | d;
        c ^ a;
        c ^ b;
        c ^ c;
        c ^ d;
        c&& a;
        c&& b;
        c&& c;
        c&& d;
        c* a;
        c* b;
        c* c;
        c* d;
        c / a;
        c / b;
        c / c;
        c / d;
        c - a;
        c - b;
        c - c;
        c - d;
        c % a;
        c % b;
        c % c;
        c % d;
        c + a;
        c + b;
        c + c;
        c + d;
        d& a;
        d& b;
        d& c;
        d& d;
        d | a;
        d | b;
        d | c;
        d | d;
        d ^ a;
        d ^ b;
        d ^ c;
        d ^ d;
        d&& a;
        d&& b;
        d&& c;
        d&& d;
        d* a;
        d* b;
        d* c;
        d* d;
        d / a;
        d / b;
        d / c;
        d / d;
        d - a;
        d - b;
        d - c;
        d - d;
        d % a;
        d % b;
        d % c;
        d % d;
        d + a;
        d + b;
        d + c;
        d + d;
    }
    if (1) {
        a = a & a | a ^ a && a * a / a - a % a + a;
        b = b & b | b ^ b && b * b / b - b % b + b;
        c = c & c | c ^ c && c * c / c - c % c + c;
        d = d & d | d ^ d && d * d / d - d % d + d;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a& a;
        a& b;
        a& c;
        a& d;
        a | a;
        a | b;
        a | c;
        a | d;
        a ^ a;
        a ^ b;
        a ^ c;
        a ^ d;
        a&& a;
        a&& b;
        a&& c;
        a&& d;
        a* a;
        a* b;
        a* c;
        a* d;
        a / a;
        a / b;
        a / c;
        a / d;
        a - a;
        a - b;
        a - c;
        a - d;
        a % a;
        a % b;
        a % c;
        a % d;
        a + a;
        a + b;
        a + c;
        a + d;
        b& a;
        b& b;
        b& c;
        b& d;
        b | a;
        b | b;
        b | c;
        b | d;
        b ^ a;
        b ^ b;
        b ^ c;
        b ^ d;
        b&& a;
        b&& b;
        b&& c;
        b&& d;
        b* a;
        b* b;
        b* c;
        b* d;
        b / a;
        b / b;
        b / c;
        b / d;
        b - a;
        b - b;
        b - c;
        b - d;
        b % a;
        b % b;
        b % c;
        b % d;
        b + a;
        b + b;
        b + c;
        b + d;
        c& a;
        c& b;
        c& c;
        c& d;
        c | a;
        c | b;
        c | c;
        c | d;
        c ^ a;
        c ^ b;
        c ^ c;
        c ^ d;
        c&& a;
        c&& b;
        c&& c;
        c&& d;
        c* a;
        c* b;
        c* c;
        c* d;
        c / a;
        c / b;
        c / c;
        c / d;
        c - a;
        c - b;
        c - c;
        c - d;
        c % a;
        c % b;
        c % c;
        c % d;
        c + a;
        c + b;
        c + c;
        c + d;
        d& a;
        d& b;
        d& c;
        d& d;
        d | a;
        d | b;
        d | c;
        d | d;
        d ^ a;
        d ^ b;
        d ^ c;
        d ^ d;
        d&& a;
        d&& b;
        d&& c;
        d&& d;
        d* a;
        d* b;
        d* c;
        d* d;
        d / a;
        d / b;
        d / c;
        d / d;
        d - a;
        d - b;
        d - c;
        d - d;
        d % a;
        d % b;
        d % c;
        d % d;
        d + a;
        d + b;
        d + c;
        d + d;

    } else {
        a = a & a | a ^ a && a * a / a - a % a + a;
        b = b & b | b ^ b && b * b / b - b % b + b;
        c = c & c | c ^ c && c * c / c - c % c + c;
        d = d & d | d ^ d && d * d / d - d % d + d;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a& a;
        a& b;
        a& c;
        a& d;
        a | a;
        a | b;
        a | c;
        a | d;
        a ^ a;
        a ^ b;
        a ^ c;
        a ^ d;
        a&& a;
        a&& b;
        a&& c;
        a&& d;
        a* a;
        a* b;
        a* c;
        a* d;
        a / a;
        a / b;
        a / c;
        a / d;
        a - a;
        a - b;
        a - c;
        a - d;
        a % a;
        a % b;
        a % c;
        a % d;
        a + a;
        a + b;
        a + c;
        a + d;
        b& a;
        b& b;
        b& c;
        b& d;
        b | a;
        b | b;
        b | c;
        b | d;
        b ^ a;
        b ^ b;
        b ^ c;
        b ^ d;
        b&& a;
        b&& b;
        b&& c;
        b&& d;
        b* a;
        b* b;
        b* c;
        b* d;
        b / a;
        b / b;
        b / c;
        b / d;
        b - a;
        b - b;
        b - c;
        b - d;
        b % a;
        b % b;
        b % c;
        b % d;
        b + a;
        b + b;
        b + c;
        b + d;
        c& a;
        c& b;
        c& c;
        c& d;
        c | a;
        c | b;
        c | c;
        c | d;
        c ^ a;
        c ^ b;
        c ^ c;
        c ^ d;
        c&& a;
        c&& b;
        c&& c;
        c&& d;
        c* a;
        c* b;
        c* c;
        c* d;
        c / a;
        c / b;
        c / c;
        c / d;
        c - a;
        c - b;
        c - c;
        c - d;
        c % a;
        c % b;
        c % c;
        c % d;
        c + a;
        c + b;
        c + c;
        c + d;
        d& a;
        d& b;
        d& c;
        d& d;
        d | a;
        d | b;
        d | c;
        d | d;
        d ^ a;
        d ^ b;
        d ^ c;
        d ^ d;
        d&& a;
        d&& b;
        d&& c;
        d&& d;
        d* a;
        d* b;
        d* c;
        d* d;
        d / a;
        d / b;
        d / c;
        d / d;
        d - a;
        d - b;
        d - c;
        d - d;
        d % a;
        d % b;
        d % c;
        d % d;
        d + a;
        d + b;
        d + c;
        d + d;
    }
    while (1) {
        a = a & a | a ^ a && a * a / a - a % a + a;
        b = b & b | b ^ b && b * b / b - b % b + b;
        c = c & c | c ^ c && c * c / c - c % c + c;
        d = d & d | d ^ d && d * d / d - d % d + d;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a& a;
        a& b;
        a& c;
        a& d;
        a | a;
        a | b;
        a | c;
        a | d;
        a ^ a;
        a ^ b;
        a ^ c;
        a ^ d;
        a&& a;
        a&& b;
        a&& c;
        a&& d;
        a* a;
        a* b;
        a* c;
        a* d;
        a / a;
        a / b;
        a / c;
        a / d;
        a - a;
        a - b;
        a - c;
        a - d;
        a % a;
        a % b;
        a % c;
        a % d;
        a + a;
        a + b;
        a + c;
        a + d;
        b& a;
        b& b;
        b& c;
        b& d;
        b | a;
        b | b;
        b | c;
        b | d;
        b ^ a;
        b ^ b;
        b ^ c;
        b ^ d;
        b&& a;
        b&& b;
        b&& c;
        b&& d;
        b* a;
        b* b;
        b* c;
        b* d;
        b / a;
        b / b;
        b / c;
        b / d;
        b - a;
        b - b;
        b - c;
        b - d;
        b % a;
        b % b;
        b % c;
        b % d;
        b + a;
        b + b;
        b + c;
        b + d;
        c& a;
        c& b;
        c& c;
        c& d;
        c | a;
        c | b;
        c | c;
        c | d;
        c ^ a;
        c ^ b;
        c ^ c;
        c ^ d;
        c&& a;
        c&& b;
        c&& c;
        c&& d;
        c* a;
        c* b;
        c* c;
        c* d;
        c / a;
        c / b;
        c / c;
        c / d;
        c - a;
        c - b;
        c - c;
        c - d;
        c % a;
        c % b;
        c % c;
        c % d;
        c + a;
        c + b;
        c + c;
        c + d;
        d& a;
        d& b;
        d& c;
        d& d;
        d | a;
        d | b;
        d | c;
        d | d;
        d ^ a;
        d ^ b;
        d ^ c;
        d ^ d;
        d&& a;
        d&& b;
        d&& c;
        d&& d;
        d* a;
        d* b;
        d* c;
        d* d;
        d / a;
        d / b;
        d / c;
        d / d;
        d - a;
        d - b;
        d - c;
        d - d;
        d % a;
        d % b;
        d % c;
        d % d;
        d + a;
        d + b;
        d + c;
        d + d;
    }
    {
        a = a & a | a ^ a && a * a / a - a % a + a;
        b = b & b | b ^ b && b * b / b - b % b + b;
        c = c & c | c ^ c && c * c / c - c % c + c;
        d = d & d | d ^ d && d * d / d - d % d + d;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a = a & b | c ^ d && a * b / c - d % a + b;
        b = b & a | c ^ d && b * a / c - d % b + a;
        c = c & d | a ^ b && c * d / a - b % c + d;
        d = d & a | b ^ c && d * a / b - c % d + a;
        a& a;
        a& b;
        a& c;
        a& d;
        a | a;
        a | b;
        a | c;
        a | d;
        a ^ a;
        a ^ b;
        a ^ c;
        a ^ d;
        a&& a;
        a&& b;
        a&& c;
        a&& d;
        a* a;
        a* b;
        a* c;
        a* d;
        a / a;
        a / b;
        a / c;
        a / d;
        a - a;
        a - b;
        a - c;
        a - d;
        a % a;
        a % b;
        a % c;
        a % d;
        a + a;
        a + b;
        a + c;
        a + d;
        b& a;
        b& b;
        b& c;
        b& d;
        b | a;
        b | b;
        b | c;
        b | d;
        b ^ a;
        b ^ b;
        b ^ c;
        b ^ d;
        b&& a;
        b&& b;
        b&& c;
        b&& d;
        b* a;
        b* b;
        b* c;
        b* d;
        b / a;
        b / b;
        b / c;
        b / d;
        b - a;
        b - b;
        b - c;
        b - d;
        b % a;
        b % b;
        b % c;
        b % d;
        b + a;
        b + b;
        b + c;
        b + d;
        c& a;
        c& b;
        c& c;
        c& d;
        c | a;
        c | b;
        c | c;
        c | d;
        c ^ a;
        c ^ b;
        c ^ c;
        c ^ d;
        c&& a;
        c&& b;
        c&& c;
        c&& d;
        c* a;
        c* b;
        c* c;
        c* d;
        c / a;
        c / b;
        c / c;
        c / d;
        c - a;
        c - b;
        c - c;
        c - d;
        c % a;
        c % b;
        c % c;
        c % d;
        c + a;
        c + b;
        c + c;
        c + d;
        d& a;
        d& b;
        d& c;
        d& d;
        d | a;
        d | b;
        d | c;
        d | d;
        d ^ a;
        d ^ b;
        d ^ c;
        d ^ d;
        d&& a;
        d&& b;
        d&& c;
        d&& d;
        d* a;
        d* b;
        d* c;
        d* d;
        d / a;
        d / b;
        d / c;
        d / d;
        d - a;
        d - b;
        d - c;
        d - d;
        d % a;
        d % b;
        d % c;
        d % d;
        d + a;
        d + b;
        d + c;
        d + d;
        +a = +a & +a | +a ^ +a && +a * +a / +a - +a % +a + +a;
        +b = +b & +b | +b ^ +b && +b * +b / +b - +b % +b + +b;
        +c = +c & +c | +c ^ +c && +c * +c / +c - +c % +c + +c;
        +d = +d & +d | +d ^ +d && +d * +d / +d - +d % +d + +d;
        +a = +a & +b | +c ^ +d && +a * +b / +c - +d % +a + +b;
        +b = +b & +a | +c ^ +d && +b * +a / +c - +d % +b + +a;
        +c = +c & +d | +a ^ +b && +c * +d / +a - +b % +c + +d;
        +d = +d & +a | +b ^ +c && +d * +a / +b - +c % +d + +a;
        +a = +a & +b | +c ^ +d && +a * +b / +c - +d % +a + +b;
        +b = +b & +a | +c ^ +d && +b * +a / +c - +d % +b + +a;
        +c = +c & +d | +a ^ +b && +c * +d / +a - +b % +c + +d;
        +d = +d & +a | +b ^ +c && +d * +a / +b - +c % +d + +a;
        +a & +a;
        +a & +b;
        +a & +c;
        +a & +d;
        +a | +a;
        +a | +b;
        +a | +c;
        +a | +d;
        +a ^ +a;
        +a ^ +b;
        +a ^ +c;
        +a ^ +d;
        +a && +a;
        +a && +b;
        +a && +c;
        +a && +d;
        +a * +a;
        +a * +b;
        +a * +c;
        +a * +d;
        +a / +a;
        +a / +b;
        +a / +c;
        +a / +d;
        +a - +a;
        +a - +b;
        +a - +c;
        +a - +d;
        +a % +a;
        +a % +b;
        +a % +c;
        +a % +d;
        +a + +a;
        +a + +b;
        +a + +c;
        +a + +d;
        +b & +a;
        +b & +b;
        +b & +c;
        +b & +d;
        +b | +a;
        +b | +b;
        +b | +c;
        +b | +d;
        +b ^ +a;
        +b ^ +b;
        +b ^ +c;
        +b ^ +d;
        +b && +a;
        +b && +b;
        +b && +c;
        +b && +d;
        +b * +a;
        +b * +b;
        +b * +c;
        +b * +d;
        +b / +a;
        +b / +b;
        +b / +c;
        +b / +d;
        +b - +a;
        +b - +b;
        +b - +c;
        +b - +d;
        +b % +a;
        +b % +b;
        +b % +c;
        +b % +d;
        +b + +a;
        +b + +b;
        +b + +c;
        +b + +d;
        +c & +a;
        +c & +b;
        +c & +c;
        +c & +d;
        +c | +a;
        +c | +b;
        +c | +c;
        +c | +d;
        +c ^ +a;
        +c ^ +b;
        +c ^ +c;
        +c ^ +d;
        +c && +a;
        +c && +b;
        +c && +c;
        +c && +d;
        +c * +a;
        +c * +b;
        +c * +c;
        +c * +d;
        +c / +a;
        +c / +b;
        +c / +c;
        +c / +d;
        +c - +a;
        +c - +b;
        +c - +c;
        +c - +d;
        +c % +a;
        +c % +b;
        +c % +c;
        +c % +d;
        +c + +a;
        +c + +b;
        +c + +c;
        +c + +d;
        +d & +a;
        +d & +b;
        +d & +c;
        +d & +d;
        +d | +a;
        +d | +b;
        +d | +c;
        +d | +d;
        +d ^ +a;
        +d ^ +b;
        +d ^ +c;
        +d ^ +d;
        +d && +a;
        +d && +b;
        +d && +c;
        +d && +d;
        +d * +a;
        +d * +b;
        +d * +c;
        +d * +d;
        +d / +a;
        +d / +b;
        +d / +c;
        +d / +d;
        +d - +a;
        +d - +b;
        +d - +c;
        +d - +d;
        +d % +a;
        +d % +b;
        +d % +c;
        +d % +d;
        +d + +a;
        +d + +b;
        +d + +c;
        +d + +d;
        -a = -a & -a | -a ^ -a && -a * -a / -a - -a % -a + -a;
        -b = -b & -b | -b ^ -b && -b * -b / -b - -b % -b + -b;
        -c = -c & -c | -c ^ -c && -c * -c / -c - -c % -c + -c;
        -d = -d & -d | -d ^ -d && -d * -d / -d - -d % -d + -d;
        -a = -a & -b | -c ^ -d && -a * -b / -c - -d % -a + -b;
        -b = -b & -a | -c ^ -d && -b * -a / -c - -d % -b + -a;
        -c = -c & -d | -a ^ -b && -c * -d / -a - -b % -c + -d;
        -d = -d & -a | -b ^ -c && -d * -a / -b - -c % -d + -a;
        -a = -a & -b | -c ^ -d && -a * -b / -c - -d % -a + -b;
        -b = -b & -a | -c ^ -d && -b * -a / -c - -d % -b + -a;
        -c = -c & -d | -a ^ -b && -c * -d / -a - -b % -c + -d;
        -d = -d & -a | -b ^ -c && -d * -a / -b - -c % -d + -a;
        -a & -a;
        -a & -b;
        -a & -c;
        -a & -d;
        -a | -a;
        -a | -b;
        -a | -c;
        -a | -d;
        -a ^ -a;
        -a ^ -b;
        -a ^ -c;
        -a ^ -d;
        -a && -a;
        -a && -b;
        -a && -c;
        -a && -d;
        -a * -a;
        -a * -b;
        -a * -c;
        -a * -d;
        -a / -a;
        -a / -b;
        -a / -c;
        -a / -d;
        -a - -a;
        -a - -b;
        -a - -c;
        -a - -d;
        -a % -a;
        -a % -b;
        -a % -c;
        -a % -d;
        -a + -a;
        -a + -b;
        -a + -c;
        -a + -d;
        -b & -a;
        -b & -b;
        -b & -c;
        -b & -d;
        -b | -a;
        -b | -b;
        -b | -c;
        -b | -d;
        -b ^ -a;
        -b ^ -b;
        -b ^ -c;
        -b ^ -d;
        -b && -a;
        -b && -b;
        -b && -c;
        -b && -d;
        -b * -a;
        -b * -b;
        -b * -c;
        -b * -d;
        -b / -a;
        -b / -b;
        -b / -c;
        -b / -d;
        -b - -a;
        -b - -b;
        -b - -c;
        -b - -d;
        -b % -a;
        -b % -b;
        -b % -c;
        -b % -d;
        -b + -a;
        -b + -b;
        -b + -c;
        -b + -d;
        -c & -a;
        -c & -b;
        -c & -c;
        -c & -d;
        -c | -a;
        -c | -b;
        -c | -c;
        -c | -d;
        -c ^ -a;
        -c ^ -b;
        -c ^ -c;
        -c ^ -d;
        -c && -a;
        -c && -b;
        -c && -c;
        -c && -d;
        -c * -a;
        -c * -b;
        -c * -c;
        -c * -d;
        -c / -a;
        -c / -b;
        -c / -c;
        -c / -d;
        -c - -a;
        -c - -b;
        -c - -c;
        -c - -d;
        -c % -a;
        -c % -b;
        -c % -c;
        -c % -d;
        -c + -a;
        -c + -b;
        -c + -c;
        -c + -d;
        -d & -a;
        -d & -b;
        -d & -c;
        -d & -d;
        -d | -a;
        -d | -b;
        -d | -c;
        -d | -d;
        -d ^ -a;
        -d ^ -b;
        -d ^ -c;
        -d ^ -d;
        -d && -a;
        -d && -b;
        -d && -c;
        -d && -d;
        -d * -a;
        -d * -b;
        -d * -c;
        -d * -d;
        -d / -a;
        -d / -b;
        -d / -c;
        -d / -d;
        -d - -a;
        -d - -b;
        -d - -c;
        -d - -d;
        -d % -a;
        -d % -b;
        -d % -c;
        -d % -d;
        -d + -a;
        -d + -b;
        -d + -c;
        -d + -d;
        a;
        b;
        c;
        d;
        1;
        1.2;
        'a';
        !a;
        !b;
        !c;
        !d;
        (1, 2, 3);
        +a;
        +b;
        +c;
        +d;
        +1;
        +1.2;
        +'a';
        +!a;
        +!b;
        +!c;
        +!d;
        +(1, 2, 3);
        -a;
        -b;
        -c;
        -d;
        -1;
        -1.2;
        -'a';
        -!a;
        -!b;
        -!c;
        -!d;
        -(1, 2, 3);
    }
    a&& a;
    a&& b;
    a&& c;
    a&& d;
    a || a;
    a || b;
    a || c;
    a || d;
    a < a;
    a < b;
    a < c;
    a < d;
    a > a;
    a > b;
    a > c;
    a > d;
    a <= a;
    a <= b;
    a <= c;
    a <= d;
    a >= a;
    a >= b;
    a >= c;
    a >= d;
    a == a;
    a == b;
    a == c;
    a == d;
    a != a;
    a != b;
    a != c;
    a != d;
    b&& a;
    b&& b;
    b&& c;
    b&& d;
    b || a;
    b || b;
    b || c;
    b || d;
    b < a;
    b < b;
    b < c;
    b < d;
    b > a;
    b > b;
    b > c;
    b > d;
    b <= a;
    b <= b;
    b <= c;
    b <= d;
    b >= a;
    b >= b;
    b >= c;
    b >= d;
    b == a;
    b == b;
    b == c;
    b == d;
    b != a;
    b != b;
    b != c;
    b != d;
    c&& a;
    c&& b;
    c&& c;
    c&& d;
    c || a;
    c || b;
    c || c;
    c || d;
    c < a;
    c < b;
    c < c;
    c < d;
    c > a;
    c > b;
    c > c;
    c > d;
    c <= a;
    c <= b;
    c <= c;
    c <= d;
    c >= a;
    c >= b;
    c >= c;
    c >= d;
    c == a;
    c == b;
    c == c;
    c == d;
    c != a;
    c != b;
    c != c;
    c != d;
    d&& a;
    d&& b;
    d&& c;
    d&& d;
    d || a;
    d || b;
    d || c;
    d || d;
    d < a;
    d < b;
    d < c;
    d < d;
    d > a;
    d > b;
    d > c;
    d > d;
    d <= a;
    d <= b;
    d <= c;
    d <= d;
    d >= a;
    d >= b;
    d >= c;
    d >= d;
    d == a;
    d == b;
    d == c;
    d == d;
    d != a;
    d != b;
    d != c;
    d != d;
    return a *
           b * c * d;
}