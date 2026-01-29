#pragma save_binary

#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit VAMP_LIB_DIR + "gtrain";

int sk_no_train(object who)
{
    if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
    {
      command("say Only true vampires may train here!");
      return 1;
    }
  
  /*
    if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
    {
      command("say Sorry " + TP->query_name() + ", but you are " +
	  "considered unworthy to train here.");
      return 1;
    }
  */
  
    return 0;
}

int arch_msg()
{
    write("You pass through the archway back into the training area.\n");
    return 0;
}

void create_vamp_room()
{
    set_short("Recreation area");

    set_long("   A small recreational area.  The equipment here appears to " +
        "be relatively unused and appears to be in perfect condition.\n");

    set_up_skills();
    add_item(({ "books", "guides", "texts" }), "A great number of guides in the " +
        "form of journals, pamphlets, scrolls and books, their subjects vary " +
        "widely...from discussions on hunting to theories on focusing mental " +
        "powers to descriptions of combat techniques.\n");

    add_item(({ "equipment", "training equipment" }),
        "Several pieces of physical training equipment are available along " +
        "with an array of texts.\n");

    add_exit("train", "east", arch_msg);
}

void
init()
{
    ::init();
    init_skill_raise();
}
