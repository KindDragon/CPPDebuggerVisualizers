'''Tools that format C++ type for reading'''
cpp_type = input("Please enter type: ")
if not cpp_type:
    cpp_type = "boost::gil::variant<boost::mpl::vector<boost::gil::image<boost::gil::pixel<unsigned char,boost::gil::layout<boost::mpl::vector1<boost::gil::gray_color_t>,boost::mpl::range_c<int,0,1> > >,0,std::allocator<unsigned char> >,boost::gil::image<boost::gil::pixel<unsigned char,boost::gil::layout<boost::mpl::vector3<boost::gil::red_t,boost::gil::green_t,boost::gil::blue_t>,boost::mpl::range_c<int,0,3> > >,0,std::allocator<unsigned char> >,boost::gil::image<boost::gil::pixel<unsigned char,boost::gil::layout<boost::mpl::vector4<boost::gil::red_t,boost::gil::green_t,boost::gil::blue_t,boost::gil::alpha_t>,boost::mpl::range_c<int,0,4> > >,0,std::allocator<unsigned char> >,boost::gil::image<boost::gil::pixel<unsigned short,boost::gil::layout<boost::mpl::vector1<boost::gil::gray_color_t>,boost::mpl::range_c<int,0,1> > >,0,std::allocator<unsigned char> >,boost::gil::image<boost::gil::pixel<unsigned short,boost::gil::layout<boost::mpl::vector3<boost::gil::red_t,boost::gil::green_t,boost::gil::blue_t>,boost::mpl::range_c<int,0,3> > >,0,std::allocator<unsigned char> >,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na,boost::mpl::na> >"
print()
indent = 0
for c in cpp_type:
    if c == "<":
        print(c)
        indent+=1
        print(indent*"    ", end="")
    elif c == ">":
        indent-=1
        print()
        print(indent*"    " + c, end="")
    elif c == ",":
        print(c, end="")
        print()
        print(indent*"    ", end="")
    else:
        print(c, end="")
