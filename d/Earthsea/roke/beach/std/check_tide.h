#ifndef TIDE
#define TIDE "/d/Earthsea/gont/beach/tides"
#endif

public int
check_tide(string str)
{
    if(!str || !parse_command(str, this_object(), "[the] 'tide' / 'tides'"))
    {
        return notify_fail("Check what? The tide?\n");
    }

    write("You estimate that it is " + TIDE->query_tide_string() +
        " right now.\n");
    return 1;
}
