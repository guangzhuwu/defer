# defer in c++
void f(){}<br/>
void test()<br/>
{<br/>
  const size_t buf_len;<br/>
  char* p=new char[buf_len];<br/>
  <strong>defer \[=\](){delete[] p;};<br/></strong>
  memset(p,0,buf_len);<br/>
  <br/>
  <strong>defer std::bind(std::less\<int\>(),1,1);<br/></strong>
  <strong>defer f;<br/></strong>
}<br/>
