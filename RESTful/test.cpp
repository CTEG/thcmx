#include <iostream>
#include <string.h>
#include <curl/curl.h>


using namespace std;

/* 
	Http请求结束的回调函数
	@ 会被调用多次，有下载到数据(http文件)就回调，直到下载完
 */
static size_t WriteFunction(void *input, size_t uSize, size_t uCount, void *avg)
{
	/* cout << "[WriteFunction]:" << endl
		 << "input=" << (char*)input << endl
		 << "elementSize=" << uSize << endl
		 << "elementCount=" << uCount << endl;*/
		 
	// 将请求返回数据input拷贝到avg中(avg为一开始curl_easy_setopt设置的参)
	size_t uLen = uSize * uCount;
	// string &sBuffer = *reinterpret_cast<string *>(avg);
	// sBuffer.append(reinterpret_cast<const char *>(input), uLen);
	string *pStr = (string *)(avg);
	pStr->append((char *)(input), uLen);
	
	// 只有返回uSize*uCount才会返回成功
	return uLen;
}

int main(int argc, char **argv)
{
	CURL *pCurl = NULL;
	CURLcode code;
	
	/* CURLcode curl_global_init(long flags)
	   @ 初始化libcurl，全局只需调一次
	   @ flags:	CURL_GLOBAL_DEFAULT 	// 等同于CURL_GLOBAL_ALL 
				CURL_GLOBAL_ALL     	// 初始化所有的可能的调用
				CURL_GLOBAL_SSL     	// 初始化支持安全套接字层
				CURL_GLOBAL_WIN32   	// 初始化win32套接字库
              	CURL_GLOBAL_NOTHING 	// 没有额外的初始化
			    ......
	 */
	code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (code != CURLE_OK) {
		cout << "curl_global_init() Err" << endl;
		return -1;
	}
	
	/* CURL *curl_easy_init()
	   @ 初始化curl生成CURL *curl指针
	 */
	pCurl = curl_easy_init();
	if (pCurl == NULL) {
		cout << "curl_easy_init() Err" << endl;
		return -1;
	}
	
	string sUrl = "www.baidu.com";
	curl_slist *pHeaders = NULL;
	string sBuffer;
	
	/* struct curl_slist *curl_slist_append(struct curl_slist * list, const char * string);
	   @ 添加Http消息头
	   @ 属性string：形式为name+": "+contents
	 */
	string header = "username: andyawang";
	pHeaders = curl_slist_append(pHeaders, header.c_str());
	
	/* CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
	   @ 设置下载属性及常用参数
	 */
	curl_easy_setopt(pCurl, CURLOPT_URL, "www.baidu.com"); 	// 访问的URL
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeaders);  // 属性头部(要不pHeader就没用了)
	curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); 			// 超时(单位S)
	curl_easy_setopt(pCurl, CURLOPT_HEADER, 1); 			// 下载数据包括HTTP头部
	
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &WriteFunction);	// !数据回调函数
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer);			// !数据回调函数的参，一般为Buffer或文件fd
	
	/* CURLcode curl_easy_perform(CURL *handle);
	   @ 开始下载
	 */
	code = curl_easy_perform(pCurl);
	if (code != CURLE_OK) {
		cout << "curl_easy_perform() Err" << endl;
		return -1;
	}
	
	/* CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ... );
	   @ 获取下载完的相关信息
	   @ info：CURLINFO_RESPONSE_CODE  	// 获取返回的Http码
			   CURLINFO_TOTAL_TIME  	// 获取总的请求下载时间
			   CURLINFO_SIZE_DOWNLOAD  	// 获取下载的文件大小
			   ......
	 */
	long retCode = 0;
	code = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE , &retCode); 
	if (code != CURLE_OK) {
		cout << "curl_easy_perform() Err" << endl;
		return -1;
	}
	cout << "[Http Return Code] : " << retCode << endl;
	cout << "[Http Context] : " << endl << sBuffer << endl;
	
	/* void curl_easy_cleanup(CURL * handle);
	   @ 释放CURL *curl指针
	 */		
	curl_easy_cleanup(pCurl);
	
	/* void curl_global_cleanup(void);
	   @ 初始化libcurl，全局也只需调一次
	 */		
	curl_global_cleanup();

	return 0;
}



// g++ -o test test.cpp -lcurl