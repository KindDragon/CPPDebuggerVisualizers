#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/variant.hpp>
#include <boost/any.hpp>
#include <boost/optional.hpp>
#include <boost/bimap.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/date_time.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/chrono.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/container/deque.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/list.hpp>
#include <boost/container/map.hpp>
#include <boost/container/set.hpp>
#include <boost/container/slist.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp> 

class Data
{
	int s;
	float f;
};

void mallocDeleter(Data*& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr=NULL;
	}
}


void TestPointerContainerLibrary()
{
	boost::ptr_array<boost::nullable<Data>, 10> b;
	b.replace(0, new Data());
	for(auto it = b.begin(); it!=b.end();it++)
		(*it);
	boost::ptr_vector<boost::nullable<Data>> d;
	d.push_back(new Data());
	d.push_back(0);
	for(auto it = d.begin(); it!=d.end();it++)
		(*it);
	boost::ptr_map<int, Data> e;
	int ival = 0;
	e.insert(ival, new Data());
	for(auto it = e.begin(); it!=e.end();it++)
		(*it);
	boost::ptr_list<Data> g;
	g.push_back(new Data());
	for(auto it = g.begin(); it!=g.end();it++)
		(*it);
	boost::ptr_deque<Data> h;
	h.push_back(new Data());
	for(auto it = h.begin(); it!=h.end();it++)
		(*it);
	boost::ptr_set<int> i;
	i.insert(new int(5));
	for(auto it = i.begin(); it!=i.end();it++)
		(*it);
	boost::ptr_multimap<int, Data> k;
	k.insert(ival, new Data());
	for(auto it = k.begin(); it!=k.end();it++)
		(*it);
	boost::ptr_multiset<int> l;
	l.insert(new int(5));
	for(auto it = l.begin(); it!=l.end();it++)
		(*it);
}

void TestSmartPointers()
{
	boost::scoped_ptr<Data> ptr(new Data());
	boost::scoped_array<Data> ptrAr(new Data[10]());
	boost::shared_ptr<Data> shPtr(new Data());
	boost::weak_ptr<Data> weakPtr(shPtr);
	boost::shared_ptr<Data> shPtrEx( new Data(), std::ptr_fun(mallocDeleter) );
	boost::shared_array<Data> shPtrAr(new Data[10]());
}

void TestVariantAnyOptional()
{
	boost::variant<int, std::string, Data> var("gdsg");
	var = 4;
	boost::variant<int, std::string, Data, bool> var2(false);
	var2 = 4;

	typedef boost::make_recursive_variant<
		int
		, std::vector< boost::recursive_variant_ >
	>::type int_tree_t;

	std::vector< int_tree_t > subresult;
	subresult.push_back(3);
	subresult.push_back(5);

	std::vector< int_tree_t > result;
	result.push_back(1);
	result.push_back(subresult);
	result.push_back(7);

	int_tree_t vartt;
	vartt = result;
	boost::any valany = 4;
	valany =  std::string("fdsfsd");
	valany = true;
	boost::optional<int> opt = 4;
}

void TestUnordered()
{
	boost::unordered_map<std::string, int> um;
	um["hfh"] = 6;
	um["jgfsjsf"] = 86;
	boost::unordered_multimap<std::string, int> umm;
	umm.insert(std::make_pair(std::string("sdhsh"), 73576));
	umm.insert(std::make_pair(std::string("sdhsh"), 34578));
	umm.insert(std::make_pair(std::string("jfsg"), 02));
	auto p = *um.begin();
	boost::unordered_set<int> us;
	us.insert(5);
	us.insert(6543765);
	us.insert(468);
	boost::unordered_multiset<int> uss;
	uss.insert(63);
	uss.insert(63);
	uss.insert(8568);
}

void TestGregorian() 
{
	using namespace boost::gregorian;
	date weekstart(2002,Feb,1);
	date_duration duration = weeks(1);
	date weekend  = weekstart + weeks(1);
	date d1 = day_clock::local_day();
	date d2 = d1 + days(5);
	if (d2 >= d1) {} //date comparison operators 

	date_period thisWeek(d1,d2);
	if (thisWeek.contains(d1)) {}//do something 

	//iterate and print the week
	day_iterator itr(weekstart);
	while (itr <= weekend) {
		++itr;
	} 

	//US labor day is first Monday in Sept 
	typedef nth_day_of_the_week_in_month nth_dow;
	nth_dow labor_day(nth_dow::first,Monday, Sep); 
	//calculate a specific date for 2004 from functor 
	date d6 = labor_day.get_date(2004); 
}

void TestPosixTime()
{
	using namespace boost::posix_time;
	boost::gregorian::date d(2002,boost::date_time::Feb,1); //an arbitrary date 
	ptime t1(d, hours(5)+microsec(100)); //date + time of day offset 
	ptime t2 = t1 - minutes(4)+seconds(2);
	ptime now = second_clock::local_time(); //use the clock 
	boost::gregorian::date today = now.date(); //Get the date part out of the time 
	boost::gregorian::date tomorrow = today + boost::gregorian::date_duration(1);
	ptime tomorrow_start(tomorrow); //midnight 

	//starting at current time iterator adds by one hour
	time_iterator titr(now,hours(1)); 
	for (; titr < tomorrow_start; ++titr) {
	}
}

void TestLocalTime()
{
	using namespace boost::local_time;
	using namespace boost::date_time;
	//setup some timezones for creating and adjusting times
	//first time zone uses the time zone file for regional timezone definitions
	tz_database tz_db;
	//tz_db.load_from_file("date_time_zonespec.csv");
	time_zone_ptr nyc_tz = tz_db.time_zone_from_region("America/New_York");
	//This timezone uses a posix time zone string definition to create a time zone
	posix_time_zone timezone("MST-07:00:00");
	time_zone_ptr phx_tz(new posix_time_zone("MST-07:00:00"));

	//local departure time in phoenix is 11 pm on April 2 2005 
	// Note that New York changes to daylight savings on Apr 3 at 2 am)
	local_date_time phx_departure(boost::gregorian::date(2005, Apr, 2), boost::posix_time::hours(23), phx_tz, 
		local_date_time::NOT_DATE_TIME_ON_ERROR);

	boost::posix_time::time_duration flight_length = boost::posix_time::hours(4) + boost::posix_time::minutes(30);
	local_date_time phx_arrival = phx_departure + flight_length;
	//convert the phx time to a nyz time
	local_date_time nyc_arrival = phx_arrival.local_time_in(nyc_tz);
}

void TestContainers()
{
	boost::dynamic_bitset<> x(70);
	x[0] = 1;
	x[1] = 1;
	x[4] = 1;

	boost::array<Data, 10> a;
	a[0] = Data();

	auto r = boost::addressof(a);
	boost::circular_buffer<int> cb(3);

	// Insert some elements into the buffer.
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.push_back(4);

	for(boost::circular_buffer<int>::const_iterator it = cb.begin(); it!=cb.end();it++)
		(*it);

	using namespace boost::container;
	deque<int> d;
	d.push_back(100);
	flat_map<int, int> fm;
	fm.insert(std::make_pair(100, 1000));
	flat_set<int> fs;
	fs.insert(100);
	list<int> l;
	l.push_back(100);
	auto it = l.cbegin();
	for (; it != l.cend(); it++)
	{
		*it;
	}
	map<int, int> m;
	m[100] = 1000;
	set<int> s;
	s.insert(100);
	slist<int> sl;
	sl.push_front(100);
	basic_string<char> str("dsfsdf");
	basic_string<char> str2("lk;lgdfkg;lka;glk''l;'sfgllllllllllllllllllllllllllllllllllll;f");
	vector<int> v;
	v.push_back(100);
	stable_vector<int> sv;
	sv.push_back(100);
}

//This is a base hook
class MyClass : public boost::intrusive::slist_base_hook<>
{
	int int_;

public:
	//This is a member hook
	boost::intrusive::slist_member_hook<> member_hook_;

	MyClass(int i)
		:  int_(i)
	{}
};

void TestIntrusive()
{
	using namespace boost::intrusive;

	//Define an slist that will store MyClass using the public base hook
	typedef slist<MyClass> BaseList;

	//Define an slist that will store MyClass using the public member hook
	typedef member_hook<MyClass, slist_member_hook<>, &MyClass::member_hook_> MemberOption;
	typedef slist<MyClass, MemberOption> MemberList;

	typedef std::vector<MyClass>::iterator VectIt;
	typedef std::vector<MyClass>::reverse_iterator VectRit;

	//Create several MyClass objects, each one with a different value
	std::vector<MyClass> values;
	for(int i = 0; i < 100; ++i)  values.push_back(MyClass(i));

	BaseList baselist;
	MemberList memberlist;

	//Now insert them in the reverse order in the base hook list
	for(VectIt it(values.begin()), itend(values.end()); it != itend; ++it)
		baselist.push_front(*it);

	//Now insert them in the same order as in vector in the member hook list
	for(BaseList::iterator it(baselist.begin()), itend(baselist.end())
		; it != itend; ++it){
			memberlist.push_front(*it);
	}

	//Now test lists
	{
		BaseList::iterator bit(baselist.begin()), bitend(baselist.end());
		MemberList::iterator mit(memberlist.begin()), mitend(memberlist.end());
		VectRit rit(values.rbegin()), ritend(values.rend());
		VectIt  it(values.begin()), itend(values.end());

		//Test the objects inserted in the base hook list
		for(; rit != ritend; ++rit, ++bit)
			if(&*bit != &*rit)
				break;

		//Test the objects inserted in the member hook list
		for(; it != itend; ++it, ++mit)
			if(&*mit != &*it)  
				break;
	}
}

int main(int, char*[])
{
	boost::tribool b(true);
	b = false;
	b = boost::indeterminate;

	boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();

	for ( long i = 0; i < 10000000; ++i )
		std::sqrt( 123.456L ); // burn some time

	boost::chrono::duration<double, boost::ratio<2,1>> sec = boost::chrono::system_clock::now() - start;

	auto tupl = boost::make_tuple(1, "terterwt", true);

	unsigned char uuid_data[16];
	// fill uuid_data

	boost::uuids::uuid u;

	memcpy(&u, uuid_data, 16);

	boost::uuids::uuid u2 =
	{ 0x12 ,0x34, 0x56, 0x78
	, 0x90, 0xab
	, 0xcd, 0xef
	, 0x12, 0x34
	, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
	};

	TestPointerContainerLibrary();

	TestSmartPointers();

	TestVariantAnyOptional();

	TestUnordered();

	TestGregorian();

	TestPosixTime();

	TestLocalTime();

	TestContainers();

	TestIntrusive();
	
	return EXIT_SUCCESS;
}