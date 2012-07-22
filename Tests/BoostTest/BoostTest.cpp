#include <iostream>
#include <array>
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

int main(int, char*[]) {
	boost::dynamic_bitset<> x(5);
	x[0] = 1;
	x[1] = 1;
	x[4] = 1;
	boost::dynamic_bitset<unsigned long> y(std::move(x));
	boost::dynamic_bitset<unsigned long> z;
	z = std::move(y);
	std::array<void*, 10> c;
	boost::array<Data, 10> a;
	a[0] = Data();
	for(auto it = a.begin(); it!=a.end();it++)
		(*it);
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
	boost::scoped_ptr<Data> ptr(new Data());
	boost::scoped_array<Data> ptrAr(new Data[10]());
	boost::shared_ptr<Data> shPtr(new Data());
	boost::shared_ptr<Data> shPtrEx( new Data(), std::ptr_fun(mallocDeleter) );
	boost::weak_ptr<Data> weakPtr(shPtr);
	boost::shared_array<Data> shPtrAr(new Data[10]());
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
	boost::optional<int> opt = 4;

	typedef boost::bimap< std::string, int > results_bimap;
	typedef results_bimap::value_type position;

	results_bimap results;
	auto itres = position("Argentina"    ,1);
	results.insert( itres );
	results.insert( position("Spain"        ,2) );
	results.insert( position("Germany"      ,3) );
	results.insert( position("France"       ,4) );
	for(auto it = results.begin(); it!=results.end();it++)
	{
		(*it);
	}
	auto fff = results.size();
	auto ooooooo = results.right.at(1);

	struct country  {};
	struct place    {};

	// Soccer World cup.

	typedef boost::bimaps::bimap
		<
		boost::bimaps::tagged< std::string, country >,
		boost::bimaps::tagged< int        , place   >

		> results_bimap2;

	typedef results_bimap2::value_type position2;

	results_bimap2 results2;
	results2.insert( position2("Argentina"    ,1) );
	results2.insert( position2("Spain"        ,2) );
	results2.insert( position2("Germany"      ,3) );
	results2.insert( position2("France"       ,4) );

	for( results_bimap2::map_by<place>::const_iterator
		i    = results2.by<place>().begin(),
		iend = results2.by<place>().end() ;
	i != iend; ++i )
	{
		std::cout << i->get<place  >() << ") "
			<< i->get<country>() << std::endl;
	}

	for( results_bimap2::map_by<country>::const_iterator
		i    = results2.by<country>().begin(),
		iend = results2.by<country>().end() ;
	i != iend; ++i )
	{
		std::cout << i->get<country>() << " ends "
			<< i->get<place  >() << "?"
			<< std::endl;
	}
	return EXIT_SUCCESS;
}