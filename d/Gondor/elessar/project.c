inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Lord Elessar's Project-room");
    set_long("This is the project-room, where Lord Elessar administrates his \n"+
      "work on the domain.\n"+
      "There are several exits here, leading to different places in Middle-earth.\n");
    add_exit("/d/Gondor/common/domain_entr","domentr",0);
    add_exit("/d/Gondor/morgul/blackrider", "nazgul",0);
    add_exit("/d/Gondor/ringquest/rq_master", "rq", 0);
    add_exit("/d/Gondor/anorien/osgiliath/bridge_master", "osg", 0);
    add_exit("/d/Gondor/minas/citadel/fountain","fountain",0,0);
    add_exit("/d/Gondor/rohan/edoras/ingate","edoras",0);
    add_exit("/d/Gondor/minas/gate1","minas",0);
    add_exit("/d/Gondor/rohan/isengard/isengate","isengard",0);
    add_exit("/d/Gondor/rohan/horn/coomb/low_vale","helm",0);
    add_exit("/d/Gondor/ithilien/road/crossroads","ithilien",0);
    add_exit("/d/Gondor/common/guild/gondor/boardhall","rangers",0);
    add_exit("/d/Gondor/common/guild/north/w_corridor","north",0);
    add_exit("/d/Gondor/common/guild/ithilien/rockchamber", "henneth", 0);
    add_exit("/d/Gondor/common/guild2/boardroom","morgul",0);
    add_exit("/d/Shire/common/bree/townr1","bree",0);
    add_exit("/d/Gondor/mordor/baraddur/throneroom","barad",0);
}

init()
{
    ::init();
    add_action("check_time","time");
    add_action("add_fumbles","fumble");
    add_action("list_players","list");
    add_action("find_items", "find");
}


list_players(string str)
{
    object *glist, *melist, *slist, *rlist, *mlist;
    int i, n;
    rlist = filter(users(), "dfilter", TO, "Rhovanion");
    slist = filter(users(), "dfilter", TO, "Shire");
    glist = filter(users(), "dfilter", TO, "Gondor");
    mlist = filter(users(), "dfilter", TO, "Mordor");
    if (lower_case(str) == "g") melist = glist;
    else if (lower_case(str) == "s") melist = slist;
    else if (lower_case(str) == "r") melist = rlist;
    else if (lower_case(str) == "m") melist = mlist;
    else
	melist = rlist + slist + glist + mlist;
    while (n<sizeof(melist)) {
	write(melist[n]->query_name()+" ("+melist[n]->query_average_stat()+") - in "+
	  file_name(ENV(melist[n])));
	if (query_idle(melist[n]) > 180) write(", idle");
	if (melist[n]->query_attack()) write(","+
	      " fighting "+melist[n]->query_attack()->query_name()+".\n");
	else write(".\n");
	n++;
    }
    return 1;
}

dfilter(object ulist, string dom)
{
    int n;
    string dummy, domstr;
    dom = capitalize(lower_case(dom));
    if (!ENV(ulist)) return 0;
    if (sscanf(file_name(ENV(ulist)),"/d/%s/%s",domstr,dummy)==2)
	if (domstr == dom) return 1;
    return 0;
}

add_fumbles()
{
    TP->add_prop(LIVE_AS_ATTACK_FUMBLE,({"You fumble!!\n","Hey, you fumbled again!!!\n","Another fumble!!\n"}));
    write("Fumble-prop added. Now try to fight.\n");
    return 1;
}

int
find_items(string str)
{
    object *weps;
    int i, s;
    object *locs;
    weps = object_clones(find_object(str));
    s = sizeof(weps);
    locs = allocate(s);
    for (i = 0; i < s; ++i)
    {
	locs[i] = ENV(weps[i]);
        if (living(locs[i]))
            write(locs[i]->query_name() + "\n");
        else
            write(file_name(locs[i]) + "\n");
    }
    return 1;
}

