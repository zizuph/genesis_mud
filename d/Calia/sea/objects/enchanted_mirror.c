
/*
 *   object:      An Enchanted Mirror for the Thalassian Create Staff
 *                Quest.
 *   coder(s):    September 5th, 2003 - Jaacar
 *    
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <math.h>

#include "defs.h"
#include SEA_QUESTS

#define LIVE_I_CREATED_AERIA_STAFF "_live_i_created_aeria_staff"

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == "Spirit Circle of Psuchae";
}

void
create_object()
{
   set_name("mirror");
   add_name("enchanted mirror");
   add_name("_enchanted_mirror_"); 
   set_adj("enchanted");
   set_short("enchanted mirror");
   set_long("This is one of the most exquisite mirrors you have ever "+
        "seen in your life. Its frame is constructed entirely of crushed "+
        "seashells and sand. The mirrored glass is flawlessly forged and "+
        "backed with the finest silver. On the mirror there is some "+
        "smokey writing you can read.\n");

   add_item(({"writing","smokey writing"}),"There is some smokey writing "+
        "on the mirror that you can read.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_M_NO_STEAL,1);
   add_prop(OBJ_I_WEIGHT, 10);
}

string
query_auto_load()
{
    return MASTER + ":";
}

int
do_read(string str)
{
    int ran_ingredients, ran_location, ran_pword;
    string player_name;

    if (!str)
        return 0;

    if (str != "writing" && str != "smokey writing")
        return 0;
    
    player_name = lower_case(TP->query_real_name());
    write("The smokey writing on the glass reads:\n\nYou have come seeking "+
        "information to create the Staff of Aeria. To complete this "+
        "undertaking, you will require two components to offer in sacrifice. "+
        "You will also have to perform a ritual in a certain location.\n"+
        "\nFor your ritual, ");
    
    ran_ingredients = NAME_TO_RANDOM(player_name,THAL_STAFF_SEED,THAL_STAFF_ITEM_V);
    switch (ran_ingredients)
    {
        case 0:               // stick + diamond
            write("you will need some type of 'stick' and a white "+
                "diamond. ");
            TP->add_prop(THAL_STAFF_ITEMS,1);
            break;
        case 1:               // staff + diamond
            write("you will need a staff of some sort and a white "+
                "diamond. ");
            TP->add_prop(THAL_STAFF_ITEMS,2);
            break;
        case 2:               // stick + opal
            write("you will need some type of 'stick' and an opal (not "+
                "a fire opal). ");
            TP->add_prop(THAL_STAFF_ITEMS,3);
            break;
        case 3:               // staff + opal
            write("you will need a staff of some sort and an opal (not "+
                "a fire opal). ");
            TP->add_prop(THAL_STAFF_ITEMS,4);
            break;
        case 4:               // stick + pearl
            write("you will need some type of 'stick' and a white "+
                "pearl. ");
            TP->add_prop(THAL_STAFF_ITEMS,5);
            break;
        default:              // staff + pearl
            write("you will need a staff of some sort and a white pearl. ");
            TP->add_prop(THAL_STAFF_ITEMS,6);
    }
    write("Once you have collected these two items, you shall need to "+
        "go to ");
    ran_location = NAME_TO_RANDOM(player_name,THAL_STAFF_SEED,THAL_STAFF_LOCA_V);
    switch (ran_location)
    {
        case 0:               
            write("the roundabout in Calia. ");
            TP->add_prop(THAL_STAFF_LOCATION,"/d/Calia/mountain/road/road19");
            break;
        case 1:               
            write("the entrance to the Elemental Temple of Calia within a hidden "
                + "valley in the Calian foothills. ");
            TP->add_prop(THAL_STAFF_LOCATION,"/d/Calia/guilds/elementalists/temple/entrance");
            break;
        case 2:               
            write("the obelisk in Thalassia. ");
            TP->add_prop(THAL_STAFF_LOCATION,"/d/Calia/sea/thalassia/obelisk");
            break;
        case 3:               
            write("the chapel in the Elemental Temple of Calia within a hidden "
                + "valley in the Calian foothills. ");
            TP->add_prop(THAL_STAFF_LOCATION,"/d/Calia/guilds/elementalists/temple/chapel");
            break;
        default:               
            write("the Gelan post office. ");
            TP->add_prop(THAL_STAFF_LOCATION,"/d/Calia/gelan/rooms/post");
            break;
    }
    write("When you are in the proper location, place your offerings on the "+
        "ground. Then you must 'exclaim' the word ");
    ran_pword = NAME_TO_RANDOM(player_name,THAL_STAFF_SEED,THAL_STAFF_WORD_V);
    switch (ran_location)
    {
        case 0:               
            write("\"dunamai\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"dunamai");
            break;
        case 1:               
            write("\"dunamis\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"dunamis");
            break;
        case 2:               
            write("\"dunatos\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"dunatos");
            break;
        case 3:               
            write("\"exousia\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"exousia");
            break;
        case 4:               
            write("\"eutonos\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"eutonos");
            break;
        case 5:               
            write("\"ischus\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"ischus");
            break;
        case 6:               
            write("\"ischuo\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"ischuo");
            break;
        case 7:               
            write("\"katargeo\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"katargeo");
            break;
        case 8:               
            write("\"katischuo\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"katischuo");
            break;
        case 9:               
            write("\"nikao\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"nikao");
            break;
        case 10:               
            write("\"hupo\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"hupo");
            break;
        default:               
            write("\"kratos\".\n");
            TP->add_prop(THAL_STAFF_PWORD,"kratos");
            break;
    }
    write("\nThis will begin the ritual and sacrifice your offerings for the "+
        "creation of the Staff of Aeria. Once the staff is completed, you "+
        "must bring it back to me so that I can activate its powers for "+
        "you (activate staff).\n\nLady Aeria\n");
    return 1;
}

void
complete_ritual(object pole, object gem)
{
    object staff;
    string word;

    word = TP->query_prop(THAL_STAFF_PWORD);
    setuid();
    seteuid(getuid(TO));
    staff=clone_object(SEA_OBJECTS+"unactivated_aeria_staff");

    if (is_spirit(TP))
    {
        write("You telepathically exclaim "+word+"!.\n");
        say(QCTNAME(TP)+" looks up to the sky for a brief moment.\n");
    }
    else
    {
        write("You exclaim "+word+"!\n");
        say(QCTNAME(TP)+" exclaims "+word+"!\n");
    }

    write("The "+pole->short()+" and "+gem->short()+" suddenly rise up "+
        "off of the ground and begin swirling around and around, rising "+
        "up higher and higher with each revolution. In a brilliant flash "+
        "of light they collide together, fusing with one another. The "+
        "newly formed staff is surrounded by a white mist, obscuring it "+
        "from vision. When the mist clears, a bright white staff gently "+
        "floats down to the ground, standing upright. You reach out and "+
        "take it.\n");
    say("The "+pole->short()+" and "+gem->short()+" that were on the ground "+
        "suddenly rise up off of the ground and begin swirling around and "+
        "around, rising up higher and higher with each revolution. In a "+
        "brilliant flash of light they collide together, fusing with one "+
        "another. The newly formed staff is surrounded by a white mist, "+
        "obscuring it from vision. When the mist clears, a bright white "+
        "staff gently floats down to the ground, standing upright. "+
        QCTNAME(TP)+" reaches out and takes it.\n");
    pole->remove_object();
    gem->remove_object();
    staff->move(TP,1);
    TP->add_prop(LIVE_I_CREATED_AERIA_STAFF,1);
}

int
do_exclaim(string str)
{
    string word, location, current_room;
    int components;
    object pole, gem;

    word = TP->query_prop(THAL_STAFF_PWORD);
    location = TP->query_prop(THAL_STAFF_LOCATION);
    current_room = file_name(environment(TP));
    components = TP->query_prop(THAL_STAFF_ITEMS);
    
    if (TP->query_prop(LIVE_I_CREATED_AERIA_STAFF))
    {
        NF("You have already created a staff!\n");
        return 0;
    }

    if (!str)
        return 0;

    if (!word)
        return 0;

    if (word != str)
    {
        NF("Exclaim what?\n");
        return 0;
    }

    if (current_room != location)
    {
        NF("You are not in the proper location to perform the ritual.\n");
        return 0;
    }

    switch(components)
    {
        case 1:
            pole = present("stick",environment(TP));
            gem = present("glittering_diamond",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'stick' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no diamond on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
        case 2:
            pole = present("staff",environment(TP));
            gem = present("glittering_diamond",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'staff' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no diamond on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
        case 3:
            pole = present("stick",environment(TP));
            gem = present("iridescent_opal",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'stick' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no opal on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
        case 4:
            pole = present("staff",environment(TP));
            gem = present("iridescent_opal",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'staff' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no opal on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
        case 5:
            pole = present("stick",environment(TP));
            gem = present("white_pearl",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'stick' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no pearl on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
        default:
            pole = present("staff",environment(TP));
            gem = present("white_pearl",environment(TP));
            
            if (!pole)
            {
                NF("There is no 'staff' on the ground.\n");
                return 0;
            }

            if (!gem)
            {
                NF("There is no pearl on the ground.\n");
                return 0;
            }
            complete_ritual(pole,gem);
            return 1;
            break;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
    add_action(do_exclaim,"exclaim");
}
