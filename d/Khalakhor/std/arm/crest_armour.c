inherit "/d/Khalakhor/std/armour";

static string gCrest_id, gCrest_desc;

void create_crest_armour() {}

nomask void
create_khalakhor_armour()
{
    set_af(this_object());
    create_crest_armour();
}

void
set_crest_id(string id)
{
    gCrest_id = id;
}

void
set_crest_desc(string desc)
{
    gCrest_desc = desc;
}

string
query_crest_id()
{
    return gCrest_id;
}

string 
query_crest_desc()
{
    return gCrest_desc;
}

public mixed
wear(object arm)
{
    setuid(); seteuid(getuid());
    if (stringp(gCrest_id) && stringp(gCrest_desc))
	clone_object("/d/Khalakhor/std/arm/crest_shadow")->add_crest(this_player(), arm);
    return 0;
}

public mixed
remove(object arm)
{
    query_worn()->remove_crest(arm);
    return 0;
}
