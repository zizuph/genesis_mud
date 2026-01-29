inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/tunnel/tunnel_door.h"

#define MAX_STATE        5
#define MIN_STATE        0
#define SKILL_LIST       ({TS_INT,TS_DIS,SS_AWARENESS})
#define POISON_FILE      (MORGUL_DIR + "obj/corpse_poison")
#define HATCH_KEY1_FILE  (MORGUL_DIR + "obj/hatch_key1")
#define OTHER_ROOM       (MORGUL_DIR + "tunnel/hiding1")

int    is = 0;                  /* status of the cocoon: 0 = complete */
int    ikey = 0;                /* was a key cloned? 0 = No */

create_object()
{
    seteuid(getuid());

    set_name("corpse");
    add_name(({"cocoon"}));

    set_short("@@short_desc");
    set_long("@@long_desc");

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME,VBFC_ME("search_time"));

    add_prop(OBJ_I_WEIGHT, 80000);
    add_prop(OBJ_I_VOLUME, 75000);
    add_prop(OBJ_M_NO_GET, "Nah, it stinks and is sticky! You don't want to touch it more than necessary.\n");
  enable_reset();
}

string short_desc()
{
    switch(is)
    {
        case 0:
            return "cocoon made of cobweb threads";
        case 1:
        case 2:
            return "corpse of an orc in a cocoon";
        case 3:
            return "corpse of an orc halfway in a cocoon";
        case 4:
            return "corpse of an orc partially in a cocoon";
        case 5:
            return "corpse of an orc";
     }
}

string long_desc()
{
    string desc;

    desc = "This is the corpse of an orc in a progressed state of decomposition. ";
    switch(is)
    {
        case 0:
            desc += "It is completely surrounded by thick cords made from the " +
                "same material that the cobweb is made of. Only the skull of the " +
                "orc is looking out of the cocoon. ";
            break;
        case 1:
            desc += "It is almost completely surrounded by thick cords made " +
                "from the same material that the cobweb is made of. Only the " +
                "skull and parts of the chest are looking out of the cocoon. " +
                "Over the rib case a few cords have been cut in two. ";
            break;
        case 2:
            desc += "Most parts of the corpse are wound in thick cords made " +
                "from the same material that the cobweb is made of. Only the " +
                "skull and the chest and abdomen are looking out of the " +
                "cocoon. Lying over the ribcase and the lower part of the body " +
                "are some cords that have been cut in two. ";
            break;
        case 3:
            desc += "The lower parts of the corpse are bound with thick cords " +
                "made from the same material that the cobweb is made of. Over " +
                "the ribcase and the arms there lie cords that were cut in two. ";
            break;
        case 4:
            desc += "The lower parts of the legs are bound with thick cords made " +
                "from the same material that the cobweb is made of. Under the upper " +
                "parts of the corpse, cords are lying that were cut to parts on top " +
                "of the corpse. ";
            break;
        case 5:
            desc += "It is lying on a bed of cords that have been cut on the " +
                "top of the corpse to free it from the cocoon of cords in which " +
                "the corpse must have been. ";
            break;
    }

    desc += "The bones are still covered with shreds of decaying flesh. " +
        "All in all, it is not a nice sight!";

    return BSN(desc);
}

void init()
{
    ::init();
    add_action("do_cut","cut");
}

int query_is() { return is; }

int set_is(int i)
{
    if(i >= MIN_STATE && i <= MAX_STATE && i > is)
    {
        is = i;
        return i;
    }
    return 0;
}

int filter_slash(object wep) { return (wep->query_dt() & W_SLASH); }

int do_cut(string str)
{
    string vb = query_verb();
    string dummy;
    object *weapons = TP->query_weapon(-1);
    int    sw = sizeof(weapons);

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "cord" && sscanf(str,"%scord%s", dummy, dummy) == 0 
            &&  str != "thread" && sscanf(str,"%sthread%s", dummy, dummy) == 0 
            &&  str != "cocoon" && sscanf(str,"%scocoon%s", dummy, dummy) == 0))
        return 0;

    NF("You do not wield any weapon to cut the cords of the cocoon!\n");
    if(!sw)
        return 0;

    weapons = filter(weapons,"filter_slash",TO);

    NF("You need a sharper weapon than the one" + (sw==1?"":"s")+
        " you are wielding!\n");
    if(!sizeof(weapons))
        return 0;

    NF(BSN("Someone already cut the cords to pieces. There are no cords left " +
        "that are long enough to be worth cutting them apart."));
    if(is >= MAX_STATE)
        return 0;

    write(BSN("You manage to cut through a few cords of the cocoon with your " + 
        weapons[0]->query_name() + ", revealing a bit more of the grisly corpse."));
    SAY(" manages to cut a few cords of the cocoon with "+TP->query_possessive()+
        " "+weapons[0]->query_name()+", revealing a bit more of the grisly corpse.\n");
    if(!OTHER_ROOM->filter_elfdagger(weapons[0]))
    {
        weapons[0]->set_dull(weapons[0]->query_dull()+1);
        weapons[0]->set_weapon_hits(weapons[0]->query_weapon_hits()+100);
    }
    is++;
    return 1;
}

int search_time() { return (12-is); }

string do_search(object searcher, string str)
{
    string result;
    object key;
    object poison;

    TP->command("puke");
    write("Searching the decaying corpse makes you sick.\n");

    poison = clone_object(POISON_FILE);
    poison->move(TP);
    poison->start_poison();
    
    switch(is)
    {
        case 0: 
            return BSN("You examine the skull of the corpse, but your search reveals nothing. " +
                "The other parts of the corpse are inaccessible inside the cocoon.");
        case 1:
            return BSN("You examine the skull and the ribcase of the corpse, " +
                "but your search reveals nothing. " +
                "The other parts of the corpse are inaccessible inside the cocoon.");
        case 2:
            result = "You search through the upper body of the corpse";
            if(TP->resolve_task(TASK_FORMIDABLE, SKILL_LIST) < 0)
                return BSN(result + ", but your search reveals nothing. The other parts of the " +
                    "are inaccessible inside the cocoon.");
            break;
        case 3:
            result = "You search through the parts of the corpse that are not hidden by the cords";
            if(TP->resolve_task(TASK_DIFFICULT, SKILL_LIST) < 0)
                return BSN(result + ", but your search reveals nothing.");
            break;
        case 4:
            result = "You search through the parts of the corpse that are not hidden by the cords";
            if(TP->resolve_task(TASK_ROUTINE, SKILL_LIST) < 0)
                return BSN(result + ", but your search reveals nothing.");
            break;
        case 5:
            result = "You search through the bones and the decaying flesh of the corpse";
            if(TP->resolve_task(TASK_SIMPLE, SKILL_LIST) < 0)
                return BSN(result + ", but your search reveals nothing.");
            break;
    }

    /* You can find the key only if you didn't do the quest yet and don't have any key yet! */
    if( TP->test_bit("Gondor",MORGUL_GROUP,MORGUL_ENTRY_BIT) 
        || present(HATCH_KEY1, TP) || present(HATCH_KEY1, ENV(TO)) || ikey )
        return BSN(result + ", but your search reveals nothing.");

    result += ". Finally, you find a key hidden deep between some shreds of foul flesh. ";

    ikey = 1;
    key = clone_object(HATCH_KEY1_FILE);
    key->move(ENV(TO));

    /* Set the prop that keeps track if you did your part in the quest */
    TP->add_prop(MORGUL_ENTRY_HATCH,1);

    return BSN(result);
}
 
void reset_object()
{
    is = 0;
    ikey = 0;
}
