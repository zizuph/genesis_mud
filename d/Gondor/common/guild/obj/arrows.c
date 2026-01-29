inherit "/std/arrow";

public void
create_arrow()
{
    set_adj("white-feathered");
    set_projectile_id("ranger_gooose_feathered_arrow");
    set_hit(38);
    set_pen(35);
    set_heap_size(48);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
	return "A fairly simple arrow with fins of white goose feathers " +
	    "and a sharp iron head.\n";
    }
    else
    {
	return "Fairly simple arrows with fins of white goose feathers " +
	    "and sharp iron heads.\n";
    }
}

