/*
 * /d/Gondor/guilds/rangers/tasks/poison_room.c
 *
 * Room used in healing task.
 * Coded by Gwyneth
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "../rangers.h"
/*
inherit RANGERS_DIR + "tasks/tracktask/tracktask_funcs";
*/

#include <composite.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define COT_NAME "cot"

int gWater = 5;
int gWhiskey = 2;
int gVials = 7;
int gHerbs = 1;
object gRanger;
string gHelper = "";

void
reset_room()
{
    ::reset_room();

    if (!objectp(gRanger))
    {
        gRanger = clone_object(RANGERS_NPC + "poisoned_npc");
        gRanger->move_living("dragging himself", TO);
        gRanger->command("sit on cot");
        gRanger->set_helper(gHelper);
    }

    gWater = 5;
    gWhiskey = 2;
    gVials = 7;
    gHerbs = 1;
}

string
table_exa()
{
    string text = "The small night table next to the bed ";

    if (gHerbs)
        text += "has a pouch full of herbs on it.\n";
    else
        text += "has nothing on it.\n";

    return text;
}

string
shelf_exa()
{
    string text = "An oil lamp sits on a low shelf", *comp_text = ({});

    if (gVials > 1)
        comp_text += ({ "a few empty vials" });
    else if (gVials > 0)
        comp_text += ({ "an empty vial" });

    if (gWater > 1)
        comp_text += ({ "some glasses of water" });
    else if (gWater > 0)
        comp_text += ({ "a glass of water" });

    if (gWhiskey > 1)
        comp_text += ({ "two glasses of whiskey" });
    else if (gWhiskey > 0)
        comp_text += ({ "a glass of whiskey" });

    if (sizeof(comp_text))
        text += ", along with " + COMPOSITE_WORDS(comp_text);

    return text + ".\n";
}

string
look_at()
{
    return "The cot is small, but comfortable. It's meant to be " +
        "used for those who are too ill to sleep in the main quarters.\n" +
        sitting_on_chair(COT_NAME, this_player(), 0);
}

void
create_gondor()
{
    set_short("a small bedroom");
    set_long("This small bedroom is lit by a single lamp set upon " +
        "a shelf. A cot covered with blankets and a pillow has its " +
        "head set against the far wall. Next to the bed is a small " +
        "night table. A cloth curtain covers the only exit.\n");
    add_exit(RANGERS_TASK + "task_room", "south");
    add_item(({ "single lamp", "lamp", "shelf" }), &shelf_exa());
    add_item("cot", &look_at());
    add_item("blankets", "Thick, soft blankets cover the cot.\n");
    add_item("pillow", "A down pillow has been placed on the cot.\n");
    add_item(({ "night table", "small night table", "small table", "table" }),
        &table_exa());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_chair(COT_NAME, "[down] [in] / [on] [the] 'cot'", 1, "on");
}

void
set_helper(string name)
{
    gHelper = name;
    if (objectp(gRanger))
        gRanger->set_helper(name);
}

int
take_something(string str)
{
    int num, i;
    object ob;
    string item;

    if (!strlen(str))
        return 0;

    if (!parse_command(str, ({}),
      "'pouch' / 'herbs' [full] [of] [herbs] [from] [small] [night] [table]"))
    {
        if (!parse_command(str, ({}), "%w [from] [the] [low] [shelf]", item))
            return 0;

        switch(item)
        {
        case "whiskey":
        case "whiskeys":
            if (!gWhiskey)
                return 0;
            item = RANGERS_OBJ + "whiskey";
            num = gWhiskey;
            gWhiskey = 0;
            break;
        case "water":
        case "waters":
            if (!gWater)
                return 0;
            item = RANGERS_OBJ + "water";
            num = gWater;
            gWater = 0;
            break;
        case "vial":
        case "vials":
            if (!gVials)
                return 0;
            item = POTION_DIR + "vial";
            num = gVials;
            gVials = 0;
            break;
        default:
            return 0;
        }

    }
    else
    {
        if (gHerbs > 0)
        {
            ob = clone_object(RANGERS_OBJ + "herbpouch");
            for (i = 0; i < 10; i++)
                clone_object(HERB_DIR + "lothore")->move(ob, 1);

            for (i = 0; i < 10; i++)
                clone_object(HERB_DIR + "suranie")->move(ob, 1);

            for (i = 0; i < 5; i++)
                clone_object(HERB_DIR + "athelas")->move(ob, 1);

            for (i = 0; i < 5; i++)
                clone_object(HERB_DIR + "attanar")->move(ob, 1);

            for (i = 0; i < 2; i++)
                clone_object(HERB_DIR + "alfirin")->move(ob, 1);

            for (i = 0; i < 2; i++)
                clone_object(HERB_DIR + "foxglove")->move(ob, 1);

            if(!ob->move(TP))
            {
                write("You take a pouch of herbs from the night table.\n");
                gHerbs = 0;
                return 1;
            }
            else
            {
                write("You cannot carry the pouch of herbs.\n");
                return 1;
            }
        }

        return 0;
    }

    for (i = 0; i < num; i++)
    {
        ob = clone_object(item);
        if (ob->move(TP) > 0)
        {
            write("You cannot carry " + ob->short() + ". It falls " +
                "from the shelf and breaks.\n");
            ob->remove_object();
            return 1;
        }
        else
        {
            if (ob->query_name() == "vial")
                write("You take an empty vial from the shelf.\n");
            else
                write("You take " + ob->short() + " from the shelf.\n");
        }
    }

    return 1;
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

void
init()
{
    ::init();

    add_action(take_something, "get");
    add_action(take_something, "pick");
    add_action(take_something, "take");

    init_room_chairs();
}

