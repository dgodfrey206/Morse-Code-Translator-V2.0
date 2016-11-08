#include <streambuf>
#include <cstring>
#include <fstream>

template<class charT>
class morse_code_buffer : public std::basic_streambuf<charT> {
  // type aliases for convenience
  using Base = std::basic_streambuf<charT>;
  using int_type = typename Base::int_type;
  using traits_type = typename Base::traits_type;
  using char_type = typename Base::char_type;
public:
  static const charT* buffer[256]; // buffer to hold alphabet/number conversion
  void init(); // initializer for buffer
  // constructor that takes the file name
  morse_code_buffer(const std::basic_string<charT>&);
  ~morse_code_buffer();
  // sink for charT converted characters
  int_type overflow(int_type);
private:
  std::basic_filebuf<charT> out; // output file buffer
};

// zero-initialize buffer
template<class charT>
const charT* morse_code_buffer<charT>::buffer[256]{};

template<class charT>
void morse_code_buffer<charT>::init() {
  // simple 1 to 1 mapping
  buffer['a'] = ".-";
  buffer['b'] = "-...";
  buffer['c'] = "-.-.";
  buffer['d'] = "-..";
  buffer['e'] = ".";
  buffer['f'] = "..-.";
  buffer['g'] = "--.";
  buffer['h'] = "....";
  buffer['i'] = "..";
  buffer['j'] = ".---";
  buffer['k'] = "-.-";
  buffer['l'] = ".-..";
  buffer['m'] = "--";
  buffer['n'] = "-.";
  buffer['o'] = "---";
  buffer['p'] = ".--.";
  buffer['q'] = "--.-";
  buffer['r'] = "--.-";
  buffer['s'] = "...";
  buffer['t'] = "-";
  buffer['u'] = "..-";
  buffer['v'] = "...-";
  buffer['w'] = ".--";
  buffer['x'] = "-..-";
  buffer['y'] = "-.--";
  buffer['z'] = "--..";
  buffer['0'] = "-----";
  buffer['1'] = ".----";
  buffer['2'] = "..---";
  buffer['3'] = "...--";
  buffer['4'] = "....-";
  buffer['5'] = ".....";
  buffer['6'] = "-....";
  buffer['7'] = "--...";
  buffer['8'] = "---..";
  buffer['9'] = "----.";
  buffer[' '] = " / ";
  buffer[','] = "--..--";
}

template<class charT>
morse_code_buffer<charT>::morse_code_buffer(const std::basic_string<charT>& path) {
  // initialize buffer and open the file for output (exceptions should be handled by user)
  init();
  out.open(path, std::ios_base::out);
}

template<class charT>
morse_code_buffer<charT>::~morse_code_buffer() {
  out.close();
}

template<class charT>
auto morse_code_buffer<charT>::overflow(int_type c) -> int_type {
  if (c == traits_type::eof())
    return traits_type::eof();
  // stream converted characters to sink
  const char_type* p = buffer[tolower(static_cast<char_type>(c))];
  return out.sputn(p, strlen(p));
}
