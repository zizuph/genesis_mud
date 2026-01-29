/*
 * /d/Gondor/morgul/tower/tower_0e.c
 * The east room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * Revision history:
 *   Added functionality for opening of a door leading
 *   into an interrogation room for the Mages of the Society.
 *     - Toby, 27-Sep-2006
 *
 *   Fixed the painting and what is shown in it.
 *   Description an surrealistic touch by Gorboth.
 *   Also the date of opening.
 *     - Toby, 29-Oct-2006
 *
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define CHAMBER      (TOWER_DIR + "interrogation_chamber.c")
#define LOG_FILE     "/d/Gondor/common/guild2/log/morgul_lever"
#define TRAP_DUNGEON "/d/Gondor/morgul/cellar/pris_2w1"
#define FOUND_LEVER  "_morgul_tower_found_lever_0e"

void    do_log(object ob, string logtxt);
int     pull_lever(string str);
int     iDoorState = 0;
int     query_door_state();
void    update_door(string sAction);
string  exa_painting();
string  exa_frame();
int     my_filter(object ob, string type);

#define DEBUG2(x)            find_player("toby")->catch_msg(x + "\n");


void create_morgul_tower_room()
{
    set_level(0);
    set_room_type("large hall");
    set_extra_long("This is the east end of the hall. A row of mighty " +
        "pillars to the northwest divides it from the central part.");

    add_item(({"hall"}), 
        "The halls extends to the southwest along a row of pillars. " +
        "Beyond the pillars lies the central part of the hall, which " +
        "you can reach by walking either north or west.\n");
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}),
        "A rows of pillars runs diagonally across the large hall from " +
        "the northeast to the southwest. They divide this part of the hall " +
        "from the rest. Each of the pillars is several yards thick and made of " +
        "black stone.\n");
    add_item(({"east wall", "east walls", "eastern wall"}), 
        "The eastern wall is as the other walls in the large hall made of " +
        "black square stone blocks. The blocks fit so well that there are " +
        "hardly any seams visible between them. The surface of the blocks " +
        "has been polished so it is very smooth and it seems to absorb light. " +
        "What makes this wall different is the guilded ashen frame hung on it.\n");
    add_item( ({"painting", "dark painting", "ominous painting"}),
        "@@exa_painting");
    add_item( ({"frame", "ashen frame", "guilded ashen frame"}),
        "@@exa_frame");
    add_item(({"lever", "small lever"}),
        "The small lever fits perfectly on the frame, as if part of it.\n");

    NO_ROOF
    FLOOR
    WALLS

    add_exit(TOWER_DIR + "tower_0ne",     "north",     0, 1);
    add_exit(TOWER_DIR + "tower_0s",      "southwest", 0, 1);
    add_exit(TOWER_DIR + "tower_0c",      "west",      0, 1);
}

int my_filter(object ob, string type)
{
    if(type == "wiz")
        return (ob->query_wiz_level());

    if(type == "lord")
        return (ob->query_nazgul() == 2);

    if(type == "nazgul")
        return (ob->query_nazgul() == 1);

    if(type == "mage")
        return (ob->query_morgul_level() > APPRENTICE_LEVEL);

    if(type == "apprentice")
        return (ob->query_morgul_level());
}


string
exa_frame()
{
    TP->add_prop(FOUND_LEVER, 1);

    return "It is tall as a man. The framework is covered in intricate scrollwork " +
           "and in the lower right corner, hidded within the scrollwork, is a small " +
           "lever.\n";
}


string
exa_painting()
{
    string str;
    int    iLordAlone;
    object *oWizards = ({}),
           *oLord, 
           *oNazgul = ({}),
           *oMages = ({}),
           *oApprentices = ({}),
           *oEttani = ({});

    oEttani = all_inventory(find_object(CHAMBER));
    oEttani  -= ({ 0 });

    if(sizeof(oEttani))
    {
       iLordAlone = sizeof(oEttani);

       oWizards = filter(oEttani, &my_filter(, "wiz"));
       oEttani -= oWizards;

       oLord = filter(oEttani, &my_filter(, "lord"));
       oEttani -= oLord;

       oNazgul = filter(oEttani, &my_filter(, "nazgul"));
       oEttani -= oNazgul;

       oMages = filter(oEttani, &my_filter(, "mage"));
       oEttani -= oMages;

       oApprentices = filter(oEttani, &my_filter(, "apprentice"));
       oEttani -= oApprentices;

DEBUG2("sizeof(oWizards): " + sizeof(oWizards));
DEBUG2("sizeof(oLord): " + sizeof(oLord));
DEBUG2("sizeof(oNazgul): " + sizeof(oNazgul));
DEBUG2("sizeof(oMages): " + sizeof(oMages));
DEBUG2("sizeof(oApprentices): " + sizeof(oApprentices));
DEBUG2("sizeof(oEttani): " + sizeof(oEttani));

       if(query_door_state())
           str = "Just inside the lower left corner of the frame there " +
                 "is a small bone white smear. ";
       else
           str = "";

       if(sizeof(oEttani) > 0)
          if(sizeof(oEttani) == 1)
             str += "Upon the black stone a dull white smear is centered " +
                    "within the frame. ";
          else 
             str += "Upon the black stone " +LANG_WNUM(sizeof(oEttani))+ 
                    " are centered within the frame.";

       if(sizeof(oApprentices) > 0)
          if(sizeof(oApprentices) == 1)
             str += "Centered above the bottom of the frame, a grey scratch " +
                    "mar the surface of the wall. ";
          else 
             str += "Centered above the bottom of the frame, " +
                    LANG_WNUM(sizeof(oApprentices))+ " grey scratches mar " +
                    "the surface of the wall. ";

       if(sizeof(oMages) > 0)
          if(sizeof(oMages) == 1)
             str += "A sickly green circle radiate outward from the center " +
                    "of the frame. ";
          else 
             str += capitalize(LANG_WNUM(sizeof(oMages)))+ " sickly green " +
                    "circle radiate outward from the center of the frame. ";

       if(sizeof(oNazgul) > 0)
          if(sizeof(oNazgul) == 1)
             str += "Just beneath the top of the frame a menacing red skull " +
                    "pulse dully. ";
          else 
             str += "Just beneath the top of the frame " +LANG_WNUM(sizeof(oNazgul))+
                    " menacing red skulls pulse dully. ";

       if((sizeof(oLord) == 1) && (iLordAlone > 1))
          str += "Above all, a radiant orange crown shines forth from the top " +
                 "of the frame itself. ";
       else if((sizeof(oLord) == 1) && iLordAlone)
          str += "From the top of the frame itself a radiant orange crown " +
                 "shines forth. ";

       if(sizeof(oWizards) > 0)
          if(sizeof(oWizards) == 1)
             str += "One sharp yellow line rests to one side near the ashen frame. ";
          else 
             str += "Along the sides of the frame there are " +LANG_WNUM(sizeof(oWizards))+
                    " yellow lines. ";

    }
    else
       if(query_door_state())
          str = "Apart from a small bone white smear just inside the lower " +
                "left corner of the frame, the black stone stares back at " +
                "you, its icy surface revealing nothing.";
       else
          str = "The black stone stares back at you, its icy surface " +
                "revealing nothing.";

    return "The painting appears to be little more than a guilded ashen " +
           "frame which has been hung on the surface of the black stone of " +
           "the wall. It reaches high, as tall as a man. "  +str+ "\n";

}

void
init()
{
    ::init();

    add_action(pull_lever, "pull");

}

void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE, ob->query_name() + " ("
      + ob->query_average_stat() + ")" + logtxt + "on: "
      + ctime(time()) + ".\n");

    return;
}

int
pull_lever(string str)
{
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (str != "lever" && str != "small lever")
        NF0("Pull what?\n");

    if ( !(TP->query_prop(FOUND_LEVER)) )
       NF0("Pull what? You do not recall having seen a lever.\n");

    write("You reach out to pull the lever in the ashen frame!\n");
    say(QCTNAME(TP) + " reaches out to pull the lever in the ashen frame!'\n");

    //if (!IS_MORGUL_MAGE(TP) || (SECURITY->query_wiz_dom(TP->query_real_name()) == "Gondor") ||
    //                             (SECURITY->query_wiz_dom(TP->query_real_name()) == "Shire") )

    if (TP->query_morgul_level() > APPRENTICE_LEVEL || (SECURITY->query_wiz_dom(TP->query_real_name()) == "Gondor") ||
                                 (SECURITY->query_wiz_dom(TP->query_real_name()) == "Shire") )
    {
        if(!query_door_state())
        {
            set_alarm(2.0, 0.0, &tell_room(TO, 
                  QCTNAME(TP) + " walks up to the ashen frame and pull a lever. " +
                  "When " +HE_SHE(TP)+ " does, the air feels thicker to breathe " +
                  "and it is as if the already still air freeze. As the pressing " +
                  "feeling disperse and you realize there is now an opening in " +
                  "the wall next to the painting.\n", TP));
            write("You walk up to the ashen frame and pull the lever. Suddenly " +
                  "the air feels thicker to breathe and it is as if the already " +
                  "still air freeze. You feel a presence searching your soul " +
                  "and when it leaves you, numb, you notice an opening in the " +
                  "wall next to the painting.\n");
            update_door("open");
         }
         else
         {
            set_alarm(2.0, 0.0, &tell_room(TO, 
                  QCTNAME(TP) + " walks up to the ashen frame and pull a lever. " +
                  "When " +HE_SHE(TP)+ " does, the air feels thicker to breathe " +
                  "and it is as if the already still air freeze. As the pressing " +
                  "feeling disperse the wall is again black and smooth, marred " +
                  "only by the ashen frame.\n", TP));
            write("When you pull the lever the air feels thicker to breathe " +
              "and it is as if the already still air freeze. You feel a " +
              "presence searching your soul and when it leaves you, numb, " +
              "you notice the wall is once again black and smooth, marred only " +
              "by the ashen frame.\n");
            update_door("close");
         }
    }
    else if(TP->query_morgul_level())
    {
        if(!query_door_state())
        {
            set_alarm(2.0, 0.0, &tell_room(TO, 
                  "As " + QTNAME(TP) + " walks up to the ashen frame and " +
                  "pull the lever the air feels thicker to breathe and it " +
                  "is as if the already still air freeze. The pressing " +
                  "feeling disperse and " +QTNAME(TP)+ "step back from the " +
                  "frame.\n", TP));
            write("You step up to the ashen frame and reach out to pull the " +
                  "lever. When you do, the air feels thicker to breathe " +
                  "and it is as if the already still air freeze. You feel a " +
                  "presence searching your soul and when it leaves you, numb, " +
                  "you step back from the frame realizing it is not for you.\n");
         }
         else
         {
            set_alarm(2.0, 0.0, &tell_room(TO, 
                  QCTNAME(TP) + " walks up to the ashen frame and pull a lever. " +
                  "When " +HE_SHE(TP)+ " does, the air feels thicker to breathe " +
                  "and it is as if the already still air freeze. As the pressing " +
                  "feeling disperse the wall is again black and smooth, marred " +
                  "only by the ashen frame.\n", TP));
            write("When you walk up to the ashen fram and pull the lever the air " +
                  "feels thicker to breathe and it is as if the already still air " +
                  "freeze. You feel a presence searching your soul and when it " +
                  "leaves you, numb, you notice the wall is once again black and " +
                  "smooth, marred only by the ashen frame.\n");
            update_door("close");
         }
    }
    else
    {
        write("When you walk up to the ashen frame and pull the lever the air " +
              "feels thicker to breathe and immediately as you do so, the air " +
              "feels thicker to breathe and a chill sweeps into the hall. A " +
              "presence invades your mind searching your soul and when it leaves " +
              "you, frozen, you realize a trapdoor has opened beneath you! Laughter " +
              "echoes lodly in your head as you fall helplessly into a dark chute.\n");
        tell_room(TO, QCTNAME(TP) + " walks up to the ashen fram and pull the " +
                  "lever. Immediately, the air feels thicker to breathe and a " +
                  "chill sweeps into the hall. A trapdoor opens beneath " + 
                  TP->query_possessive() + " feet!\n", TP);
        TP->move_living("falling into a dark chute", TRAP_DUNGEON);
    }

    return 1;
}

int
query_door_state()
{
    return iDoorState;
}

void
update_door(string sAction)
{
    if(sAction == "open")
    {
        add_exit(TOWER_DIR + "interrogation_chamber", "enter", 0, 1, 0);
        iDoorState = 1;
    }

    if(sAction == "close")
    {
        remove_exit("enter");
        iDoorState = 0;
    }
}
