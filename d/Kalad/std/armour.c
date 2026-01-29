inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Kalad/std/volume";

public varargs string
short(object for_obj)
{
    string res;

    if (!obj_short)
    {
	remove_adj("unworn");
	res = ::short(for_obj);
	add_adj("unworn");
	return res;
    }
    else
    {
	return ::short(for_obj);
    }
}

void
create_armour()
{
    ::create_armour();
}
