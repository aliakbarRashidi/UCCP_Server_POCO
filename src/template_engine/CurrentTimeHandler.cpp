#include "CurrentTimeHandler.h"

#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/URI.h>
#include <Poco/URIStreamFactory.h>
#include <Poco/XML/XMLWriter.h>
#include <fstream>
#include <iostream>

#include "database/database.h"
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <assert.h>
#include <list>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>

void CurrentTimeHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
					   Poco::Net::HTTPServerResponse &response)
{

	// NOTE START workaround testing database only for test insertBooks
	Database::Book book;
	book.author = "behnam";
	Database::BookPart bookPart;
	bookPart.id = 0;
	bookPart.name = "anghezi";
	book.parts.push_back(bookPart);
	std::string bookId{"0"};

	// Database::deleteBook(bookId);
	// Database::saveBook(book);
	std::string author{"behnam"};
	int partIndex{0};
	int commentIndex{0};
	//	std::string bookName{"Book Name"};

	//	Database::insertPart(bookPart, author);
	//	bookPart.id = 1;

	//	Database::insertPart(bookPart, author);
	Database::Comment comment;
	comment.content = "hello66";
	// Database::insertBookComment(comment, author);
	// Database::deleteBookComment(bookId, partIndex, commentIndex);
	//	int partIndex{1};

	// Database::deleteBookPart(bookId, partIndex);
	Database::deleteBookPartComment(bookId, partIndex, commentIndex);

	// Database::insertBookPartComment(comment, bookId, author, partIndex);
	//	Database::User user;
	//	user.userName = "behnam";

	//	//	Database::saveUser(user);
	//	user.email = "behnamsabaghi@gmail.com";
	//	Database::updateUser(user);
	//	std::clog << Database::getBooks(author) << std::endl;

	// **********************************

	// std::clog << std::this_thread::get_id() << std::endl;
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

	Poco::DateTime now;
	std::string timeString(Poco::DateTimeFormatter::format(
	now, Poco::DateTimeFormat::SORTABLE_FORMAT));

	std::ifstream infile("content.txt");
	std::string content((std::istreambuf_iterator<char>(infile)),
			(std::istreambuf_iterator<char>()));
	std::ostream &responseStream = response.send();
	//	responseStream << "<html><head><head><title>UCCP</title></head>";
	//	responseStream << "<body><h1>Current Time</h1><p>";
	//	responseStream << (content);
	//	responseStream << "</p></body></html>";

	// objects
	//		std::string json = "{ \"test\" : { \"property\" : \"value\" }
	//}";
	//		Poco::JSON::Parser parser;
	//		Poco::Dynamic::Var result = parser.parse(json);
	//	Poco::Dynamic::Var tt = ("\"ali\":56");
	//	Poco::JSON::Object::Ptr object =
	// result.extract<Poco::JSON::Object::Ptr>();
	//	Poco::Dynamic::Var test = object->get("test");
	//	object = test.extract<Poco::JSON::Object::Ptr>();
	//	test = object->get("property");
	//	std::string value = test.convert<std::string>();
	//	responseStream << json;

	Poco::JSON::Object booksObj;
	booksObj.set("author", "FONQRI");
	Poco::JSON::Array bookObjList;
	Poco::JSON::Object bookObj;
	bookObj.set("id", 0);
	bookObj.set("name", "book name");
	bookObj.set("type", "novel");
	bookObj.set("version", 0);

	Poco::JSON::Array bookTags;
	bookTags.add("love");
	bookTags.add("fun");
	bookObj.set("tags", bookTags);

	bookObj.set("sharedMode", "private");
	bookObj.set("seensCount", 0);
	bookObj.set("likesCount", 0);

	Poco::JSON::Array likedUsersList;
	likedUsersList.add("ali");
	likedUsersList.add("behnam");

	bookObj.set("likedUsers", likedUsersList);

	Poco::JSON::Array SharedWithList;
	SharedWithList.add("ali");
	SharedWithList.add("behnam");
	bookObj.set("SharedWith", SharedWithList);

	Poco::JSON::Object bookCommentsObj;
	bookCommentsObj.set("id", "user id");
	bookCommentsObj.set("dateTime", "Date and Time");
	bookCommentsObj.set("edited", false);

	bookObj.set("comments", bookCommentsObj);

	Poco::JSON::Array bookPartsArray;
	Poco::JSON::Object bookPartObj;
	bookPartObj.set("id", 0);
	bookPartObj.set("name", "part name");
	bookPartObj.set("version", 0);
	bookPartObj.set("seensCount", 0);
	bookPartObj.set("likesCount", 0);
	bookPartObj.set("content", "content");
	bookPartsArray.add(bookPartObj);

	Poco::JSON::Array partCommentsArray;
	Poco::JSON::Object partCommentsObj;
	partCommentsObj.set("id", "user id");
	partCommentsObj.set("dateTime", "Date and time");
	partCommentsObj.set("edited", false);
	bookPartObj.set("content", "content");

	partCommentsArray.add(partCommentsObj);
	bookPartObj.set("comments", partCommentsArray);

	bookObj.set("parts", bookPartsArray);
	bookObjList.add(bookObj);

	booksObj.set("Book", bookObjList);

	//	std::stringstream ss;
	//	booksObj.stringify(ss);
	//	auto str = ss.str();
	//	responseStream << str;

	responseStream << Database::getBooks(author);
	//	// array of objects
	//	std::string json =
	//	"[ {\"test\" : 0}, { \"test1\" : [1, 2, 3], \"test2\": 4 } ]";
	//	Poco::JSON::Parser parser;
	//	Poco::Dynamic::Var result = parser.parse(json);
	//	Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
	//	Poco::JSON::Object::Ptr object = arr->getObject(1); //

	//    object = arr->getObject(1);
	//    arr = object->getArray("test1");
	//    result = arr->get(0);
	// responseStream << object->get("test2").convert<int>();
}
