#define int_p_NULL NULL
#include <iostream>
#include <boost/any.hpp>
#include <boost/atomic.hpp>
#include <boost/bimap.hpp>
#include <boost/chrono.hpp>
#include <boost/circular_buffer.hpp>
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
#include <boost/date_time.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/make_shared.hpp>
#include <boost/multi_array.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/rational.hpp>
#include <boost/regex.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/variant.hpp>
#include <boost/weak_ptr.hpp>

void TestAtomic()
{
    boost::atomic_flag f;
    f.test_and_set();
    boost::atomic<int> a(5);
}

class Data
{
public:
    Data() : s(3), f(7.77f) {}
    int s;
    float f;
    void Test() {}
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
    int ival = 33;
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

void TestGil()
{
    try
    {
        using namespace boost::gil;
        rgb8_image_t img;
        png_read_and_convert_image("test_image.png", img);
        typedef boost::mpl::vector<gray8_image_t, rgb8_image_t, rgba8_image_t, gray16_image_t, rgb16_image_t> my_images_t;
        any_image<my_images_t> dyn_img;
        png_read_image("test_image.png", dyn_img);
    }
    catch (std::ios_base::failure)
    {
    }
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
    nth_dow labor_day(nth_dow::first, Monday, Sep);
    labor_day.to_string();
    //calculate a specific date for 2004 from functor
    date d3 = labor_day.get_date(2004);
    auto ds = to_simple_string(weekstart);
    auto ds3 = to_simple_string(d3);
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
    auto ts = boost::posix_time::to_simple_string(tomorrow_start);

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
    auto tzs = timezone.to_posix_string();
    auto tds = boost::posix_time::to_simple_string(flight_length);
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
    vector<int> v;
    v.push_back(100);
    for (vector<int>::const_iterator it = v.cbegin(); it != v.cend(); it++)
        (*it);
    stable_vector<int> sv;
    sv.push_back(100);
    for (stable_vector<int>::const_iterator it = sv.cbegin(); it != sv.cend(); it++)
        (*it);
    deque<int> d;
    d.push_back(100);
    for (deque<int>::const_iterator it = d.begin(); it != d.end();it++)
        (*it);
    flat_map<int, int> fm;
    fm.insert(std::make_pair(100, 1000));
    for(flat_map<int, int>::const_iterator it = fm.begin(); it!=fm.end();it++)
        (*it);
    flat_set<int> fs;
    fs.insert(100);
    for(flat_set<int>::const_iterator it = fs.begin(); it!=fs.end();it++)
        (*it);
    list<int> l;
    l.push_back(100);
    for (auto it = l.cbegin(); it != l.cend(); it++)
    {
        *it;
    }
    slist<int> sl;
    sl.push_front(100);
    for(slist<int>::const_iterator it = sl.begin(); it!=sl.end();it++)
        (*it);
    map<int, int> m;
    m[100] = 1000;
    for(map<int, int>::const_iterator it = m.begin(); it!=m.end();it++)
        (*it);
    set<int> s;
    s.insert(100);
    for(set<int>::const_iterator it = s.begin(); it!=s.end();it++)
        (*it);
    basic_string<char> str("dsfsdf");
    basic_string<char> str2("lk;lgdfkg;lka;glk''l;'sfgllllllllllllllllllllllllllllllllllll;f");
    basic_string<wchar_t> wstr(L"dsfsdf");
    basic_string<wchar_t> wstr2(L"lk;lgdfkg;lka;glk''l;'sfgllllllllllllllllllllllllllllllllllll;f");
}

class MyClass : public boost::intrusive::list_base_hook<>   //This is a derivation hook
{
    int int_;

public:
    //This is a member hook
    boost::intrusive::list_member_hook<> member_hook_;

    MyClass(int i)
        :  int_(i)
    {}
};

//Define a list that will store MyClass using the public base hook
typedef boost::intrusive::list<MyClass>   BaseList;

//Define a list that will store MyClass using the public member hook
typedef boost::intrusive::list< MyClass
    , boost::intrusive::member_hook< MyClass, boost::intrusive::list_member_hook<>, &MyClass::member_hook_>
> MemberList;

//This is a base hook
class MyClassS : public boost::intrusive::slist_base_hook<>
{
    int int_;

public:
    //This is a member hook
    boost::intrusive::slist_member_hook<> member_hook_;

    MyClassS(int i)
        :  int_(i)
    {}
};

void TestIntrusiveList()
{
    using namespace boost::intrusive;

    BaseList baselist;

    MyClass val1(100);

    //Now insert them in the reverse order in the base hook list
    baselist.push_front(val1);
    for (auto it = baselist.begin(); it != baselist.end(); it++)
    {
        *it;
    }

    MemberList memberlist;

    MyClass val2(100);

    //Now insert them in the same order as in vector in the member hook list
    memberlist.push_back(val2);
    for (auto it = memberlist.begin(); it != memberlist.end(); it++)
    {
        *it;
    }

    //Define an slist that will store MyClass using the public base hook
    typedef slist<MyClassS> BaseListS;

    //Define an slist that will store MyClass using the public member hook
    typedef member_hook<MyClassS, slist_member_hook<>, &MyClassS::member_hook_> MemberOptionS;
    typedef slist<MyClassS, MemberOptionS> MemberListS;

    BaseListS baselists;
    MyClassS vals1(200);

    //Now insert them in the reverse order in the base hook list
    baselists.push_front(vals1);
    for (auto it = baselists.begin(); it != baselists.end(); it++)
    {
        *it;
    }

    MemberListS memberlists;
    MyClassS vals2(300);

    //Now insert them in the same order as in vector in the member hook list
    memberlists.push_front(vals2);
    for (auto it = memberlists.begin(); it != memberlists.end(); it++)
    {
        *it;
    }

    // Clearing the containers means we avoid the boost debug assertion for
    // a safe_link hook that checks whether the contained object is still
    // linked to a container when the object is deleted.
    baselists.clear();
    memberlists.clear();
    baselist.clear();
    memberlist.clear();
}

struct Belem : public boost::intrusive::set_base_hook<>
{
    int mval;
    Belem(int val) : mval(val) {}
    bool operator<(const Belem& other) const {return mval < other.mval;}
    bool operator>(const Belem& other) const {return mval > other.mval;}
    bool operator==(const Belem& other) const {return mval == other.mval;}
};
typedef boost::intrusive::set<Belem> Container;

void TestIntrusiveSet_BaseHook()
{
    Container container;
    Belem belem1(1);
    Belem belem2(2);
    container.insert(belem1);
    container.insert(belem2);
    Container::iterator itr = container.begin();
    Container::const_iterator citr = container.begin();
    Container::iterator enditr = container.end();
    container.clear();
}

struct Melem
{
    int mval;
    boost::intrusive::set_member_hook<> mhook;
    Melem(int val) : mval(val) {}
    bool operator<(const Melem& other) const {return mval < other.mval;}
    bool operator>(const Melem& other) const {return mval > other.mval;}
    bool operator==(const Melem& other) const {return mval == other.mval;}
};
typedef boost::intrusive::member_hook<Melem, boost::intrusive::set_member_hook<>, &Melem::mhook> MemberHookOptions;
typedef boost::intrusive::set<Melem, MemberHookOptions> MContainer;

void TestIntrusiveSet_MemberHook()
{
    MContainer container;
    Melem melem1(1);
    Melem melem2(2);
    container.insert(melem1);
    container.insert(melem2);
    MContainer::iterator itr = container.begin();
    MContainer::const_iterator citr = container.begin();
    container.clear();
}

struct Belem_NoSz : public boost::intrusive::set_base_hook<>
{
    int mval;
    Belem_NoSz(int val) : mval(val) {}
    bool operator<(const Belem_NoSz& other) const {return mval < other.mval;}
    bool operator>(const Belem_NoSz& other) const {return mval > other.mval;}
    bool operator==(const Belem_NoSz& other) const {return mval == other.mval;}
};
typedef boost::intrusive::set<Belem_NoSz, boost::intrusive::constant_time_size<false> > Container_NoSz;

void TestIntrusiveSet_BaseHook_NoSizeMember()
{
    Container_NoSz container;
    Belem_NoSz belem1(1);
    Belem_NoSz belem2(2);
    container.insert(belem1);
    container.insert(belem2);
    Container_NoSz::iterator itr = container.begin();
    Container_NoSz::const_iterator citr = container.begin();
    container.clear();
}

struct Melem_NoSz
{
    int mval;
    boost::intrusive::set_member_hook<> mhook;
    Melem_NoSz(int val) : mval(val) {}
    bool operator<(const Melem_NoSz& other) const {return mval < other.mval;}
    bool operator>(const Melem_NoSz& other) const {return mval > other.mval;}
    bool operator==(const Melem_NoSz& other) const {return mval == other.mval;}
};
typedef boost::intrusive::member_hook<Melem_NoSz, boost::intrusive::set_member_hook<>, &Melem_NoSz::mhook> MemberHookOptions_NoSz;
typedef boost::intrusive::set<Melem_NoSz, MemberHookOptions_NoSz, boost::intrusive::constant_time_size<false> > MContainer_NoSz;

void TestIntrusiveSet_MemberHook_NoSizeMember()
{
    MContainer_NoSz container;
    Melem_NoSz melem1(1);
    Melem_NoSz melem2(2);
    container.insert(melem1);
    container.insert(melem2);
    MContainer_NoSz::iterator itr = container.begin();
    MContainer_NoSz::const_iterator citr = container.begin();
    container.clear();
}

void TestIntrusiveSet()
{
    TestIntrusiveSet_BaseHook();
    TestIntrusiveSet_MemberHook();
    TestIntrusiveSet_BaseHook_NoSizeMember();
    TestIntrusiveSet_MemberHook_NoSizeMember();
}

void TestMultiArray()
{
    // Create a 3D array that is 3 x 4 x 2
    typedef boost::multi_array<double, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[3][4][2]);

    // Assign values to the elements
    int values = 0;
    for (index i = 0; i != 3; ++i)
        for (index j = 0; j != 4; ++j)
            for (index k = 0; k != 2; ++k)
                A[i][j][k] = values++;

    typedef boost::multi_array<double, 2> array_type_2D;
    array_type_2D myarray(boost::extents[3][4]);
    typedef boost::multi_array_types::index_range range;
    array_type_2D::array_view<2>::type myview =
        myarray[boost::indices[range(1, 3)][range(0, 4, 2)]];

    for (array_type_2D::index i = 0; i != 2; ++i)
        for (array_type_2D::index j = 0; j != 2; ++j)
            myview[i][j];
}

void TestMultiprecision()
{
    boost::multiprecision::cpp_int n("1522605");
    boost::multiprecision::cpp_int n2("15226050279");
    boost::multiprecision::cpp_int n3("152260502792253336053561837813263742971806");
    boost::multiprecision::cpp_dec_float_50 nf("152260502792253336.053561837813263742971806");
    boost::multiprecision::cpp_dec_float_100 nf100("1522605027922533.36053561837813263742971806");
}

void display(int depth, boost::property_tree::ptree& tree)
{
    using boost::property_tree::ptree;
    BOOST_FOREACH(ptree::value_type const&v, tree.get_child("")) {
        ptree subtree = v.second;
        std::string nodestr = tree.get<std::string>(v.first);

        // print current node
        //if (nodestr.length() > 0)
        //	cout << "=\"" << tree.get<string>(v.first) << "\"";

        // recursive go down the hierarchy
        display(depth + 1, subtree);
    }
}

void TestPropertyTree()
{
    using boost::property_tree::ptree;
    ptree pt;
    std::ifstream input("test.xml");
    read_xml(input, pt);
    display(0, pt);
}

void TestRational()
{
    boost::rational<int> r(15, 3);
    boost::rational<int> r2(5, 10);
}

void TestRegex()
{
    boost::regex e("a(b+|((c)*))+d");
    std::string text("abd");
    boost::smatch what;
    boost::regex_match(text, what, e, boost::match_extra);
}

void TestSmartPointers()
{
    boost::scoped_ptr<Data> ptr(new Data());
    ptr->Test();
    boost::scoped_array<Data> ptrAr(new Data[10]());
    ptrAr[0].Test();
    boost::shared_ptr<Data> shPtr(new Data());
    shPtr->Test();
    boost::weak_ptr<Data> weakPtr(shPtr);
    boost::shared_ptr<Data> shPtrEx(new Data(), std::ptr_fun(mallocDeleter));
    shPtrEx->Test();
    boost::shared_array<Data> shPtrAr(new Data[10]());
    shPtrAr[0].Test();
}

void TestUblas()
{
    using namespace boost::numeric::ublas;
    vector<double> v(3);
    mapped_vector<double> mv(3, 3);
    mv[2] = 2.0;
    mv[1] = 4.0;
    compressed_vector<double> cv(3, 3);
    cv[2] = 102.0;
    cv[1] = 101.0;
    cv[0] = 100.0;
    coordinate_vector<double> rv(3, 3);
    rv[2] = 102.0;
    rv[1] = 101.0;
    rv[0] = 100.0;
    matrix<double> m(3, 4);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            m(i, j) = i * 100 + j;
    identity_matrix<double> im(3);
    zero_matrix<double> zm(3, 3);
    scalar_matrix<double> sm(3, 3);
}

void TestUnordered()
{
    boost::unordered_map<std::string, int> um;
    um["hfh"] = 73576;
    um["jgfsjsf"] = 65;
    boost::unordered_map<std::string, boost::unordered_set<int> > um2;
    um2["dsfgal;sg"].insert(43534);
    um2["dsfgal;sg"].insert(563);
    um2["'/lreg"].insert(646);
    um2["lfdhk"].insert(752);
    boost::unordered_multimap<std::string, int> umm;
    umm.insert(std::make_pair(std::string("sdhsh"), 73576));
    umm.insert(std::make_pair(std::string("sdhsh"), 34578));
    umm.insert(std::make_pair(std::string("jfsg"), 2));
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

void TestValueInitialized()
{
    boost::value_initialized<int> vi_int;
    boost::value_initialized<double> vi_double;
    // vi_int == 0 and vi_double == 0.0

    // change values
    get(vi_int) = 42;
    get(vi_double) = 12.34;
}

class visitor
    : public boost::static_visitor < >
{
public:
    template <typename T>
    void operator()(T & i) const
    {
        i;
    }
};

void TestVariantAnyOptional()
{
    boost::variant<int, std::string, Data> var("gdsg");
    var = 4;
    boost::variant<int, std::string, Data, bool> var2(false);
    var2 = 4;

    typedef boost::make_recursive_variant <
        int,
        std::string,
        std::vector < boost::recursive_variant_ >
    > ::type int_tree_t;

    std::vector< int_tree_t > subresult;
    subresult.push_back("sadsad");
    subresult.push_back(5);

    int_tree_t vartt;
    vartt = subresult;
    std::vector < int_tree_t >& v = boost::get<std::vector < int_tree_t >>(vartt);
    v[0] = 10;

    std::vector< int_tree_t > result;
    result.push_back(1);
    result.push_back(subresult);
    result.push_back("ahgsh");
    // TODO: result[1] doesn't work ATM, cannot detect when boost::variant use boost::recursive_wrapper
    boost::apply_visitor(visitor(), result[1]);
    result.push_back(7);

    typedef boost::mpl::vector4<int, std::string, Data, bool> vec4_t;
    boost::make_variant_over<vec4_t>::type variant_from_mpl_v4; // now contains int
    variant_from_mpl_v4 = std::string("Hello word!");

    typedef boost::mpl::vector<Data, std::string, int, bool, double> vec_t;
    boost::make_variant_over<vec_t>::type variant_from_mpl_v; // now contains Data
    variant_from_mpl_v = true;
    variant_from_mpl_v = variant_from_mpl_v4;

    // Testing variant representation on BIG MPL vectors
    typedef boost::mpl::vector20 <
        boost::array<char, 1>, boost::array<char, 2>, boost::array<char, 3>, boost::array<char, 4>, boost::array<char, 5>,
        boost::array<char, 6>, boost::array<char, 7>, boost::array<char, 8>, boost::array<char, 9>, boost::array<char, 10>,
        boost::array<char, 11>, boost::array<char, 12>, boost::array<char, 13>, boost::array<char, 14>, boost::array<char, 15>,
        boost::array<char, 16>, boost::array<char, 17>, boost::array<char, 18>, boost::array<char, 19>, boost::array < char, 20 >
    > vec20_t;
    boost::make_variant_over<vec20_t>::type variant20;
    variant20 = boost::array<char, 19>();

    boost::any valany = 4;
    valany = std::string("fdsfsd");
    valany = true;
    int val = 5;
    boost::optional<int> opt = 4;
    boost::optional<int&> optRef = val;

    boost::string_view sv("boost::string_view");
    boost::wstring_view wsv(L"boost::wstring_view");

    boost::string_ref rsv("boost::string_ref");
    boost::wstring_ref rwsv(L"boost::wstring_ref");
}

struct s{};
int main(int argc, const char* argv[])
{
    boost::filesystem::path p (argv[0]);   // p reads clearer than argv[1] in the following code

    boost::filesystem::file_status status;
    if (boost::filesystem::exists(p))    // does p actually exist?
    {
        boost::filesystem::directory_iterator dit;
        dit = boost::filesystem::directory_iterator(p.parent_path());
        dit;
    }

    boost::tribool b(true);
    b = false;
    b = boost::indeterminate;

    boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();

    for ( long i = 0; i < 10000000; ++i )
        std::sqrt( 123.456L ); // burn some time

    boost::chrono::duration<double, boost::ratio<2,1>> sec = boost::chrono::system_clock::now() - start;

    auto tupl = boost::make_tuple(1, "terterwt", true);

    std::pair<int const, bool> p1;
    std::pair<int const, s> p2;
    std::pair<int const, const s> p3;
    std::pair<int const, s*> p4;
    std::pair<int const, boost::tribool> p5;
    std::pair<int const, boost::filesystem::path> p6;
    std::pair<int const, boost::unordered_set<int>> p7;
    std::pair<int const, std::unique_ptr<s>> p8;

    boost::uuids::string_generator gen;
    boost::uuids::uuid u1 = gen("{92EC2A54-C1FA-42CB-B9F9-2602D507AD17}");

    TestAtomic();

    TestContainers();

    TestGil();

    TestGregorian();

    TestIntrusiveList();

    TestIntrusiveSet();

    TestLocalTime();

    TestMultiArray();

    TestMultiprecision();

    TestPointerContainerLibrary();

    TestPosixTime();

    TestPropertyTree();

    TestRational();

    TestRegex();

    TestSmartPointers();

    TestUblas();

    TestUnordered();

    TestValueInitialized();

    TestVariantAnyOptional();

    return EXIT_SUCCESS;
}
