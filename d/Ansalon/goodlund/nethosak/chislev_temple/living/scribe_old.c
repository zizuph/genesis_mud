inherit "/d/Ansalon/std/monster";
inherit "/std/act/domove";
inherit "/lib/unique";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/goodlund/nethosak/chislev_temple/local.h"

void
create_krynn_monster()
{
    if(!IS_CLONE)
        return;

    set_name("draxus");
    add_name("scribe");
    set_living_name("draxus");
    set_title("the Scribe of Sanction");

    set_adj("tall");
    add_adj("brown-robed");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("This man was clearly not built for travel "+
    "with his tall and skinny body and pasty complexion, "+
    "it looks as if he has never seen the light of day.\n"+
    "He is carrying a bundle of maps, tending to them with "+
    "great care.\n");

    set_stats(({105,125,100+random(10),160,170,118}));

    set_random_move(random(10) + 30);

    set_alignment(0);

    set_act_time(25);
    add_act("emote looks through a heap of maps as if to "+
    "find his bearings.");
    add_act("emote mumbles something about a library and "+
    "what treasures it may contain.");
    add_act("emote is startled by a noise.");
    
    add_ask(({"quest","task","help"}),"emote dismisses you "+
    "in an unpleasant manner, making it clear that his "+
    "interests lie elsewhere.",1);
    
    add_ask(({"map","maps","mithas","library", "treasure"}),
    "emote looks at you with a terrified expression and "+
    "holds onto his maps as if his life depended on it.",1);
}

void
add_introduced(string name)
{
    command("introduce me to " + name);
}

void
gather_maps()
{
    // TEST START
    object ob    = clone_object(TDIR + "obj/test_wrap");
    ob->move(this_object(),1);
    ob->reset_wrap();
    // TEST END
    
    //object ob    = clone_object(TDIR + "map/mithas_map")->move(this_object(),1);
    //object ob1   = clone_object(TDIR + "map/ansalon_map")->move(this_object(),1);
    //object ob2   = clone_object(TDIR + "map/balifor_map")->move(this_object(),1);
    //object ob3   = clone_object(TDIR + "map/barren_map")->move(this_object(),1);
    //object ob4   = clone_object(TDIR + "map/bloodbay_map")->move(this_object(),1);
    //object ob5   = clone_object(TDIR + "map/flotsam_map")->move(this_object(),1);
    //object ob6   = clone_object(TDIR + "map/kendermore_map")->move(this_object(),1);
}
void
init_living()
{
    gather_maps();
    ::init_living();
}