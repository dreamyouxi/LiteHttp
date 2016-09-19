#ifndef __DEFS__
#define  __DEFS__

 

#define  LITEHTTP_VER   "0.1"

   // #define  LOG(MSG)  std::cout<< "[LOG]:" <<  MSG<<std::endl\



  void LOG(const char *str, ...);






#define  ERR_PORT_ERROR "port has been occupy"
 


static char *head =
"HTTP/1.0 200 OK\n"
"Content-Type: text/html\n\n";

static char *head_js =
"HTTP/1.0 200 OK\n"
"Content-Type: application/x-javascript\n\n";


static char *head_404 =
"HTTP/1.0 200 OK\n"
"Content-Type: text/html\n\n";


static char *head_css =
"HTTP/1.0 200 OK\n"
"Content-Type: 	text/css\n\n";


static char *head_png =
"HTTP/1.0 200 OK\n"
"Content-Type: 	image/png\n\n";


static char *head_jpg =
"HTTP/1.0 200 OK\n"
"Content-Type: 	image/jpeg\n\n";


static char *head_exe =
"HTTP/1.0 200 OK\n"
"Content-Type: 	application/x-msdownload\n\n";





static char *Defaulthtml =
"<html><head><title>我的第一个 HTML 页面</title></head><body>""<p>body 元素的内容会显示在浏览器中。</p>"
"<p>title 元素的内容会显示在浏览器的标题栏中。</p>"
"</body></html>";


static char *html404 ="404 Not Found";




#endif