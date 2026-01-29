
/*     Training room for the Heren Istimor guild.   */

/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

#pragma save_binary

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "heren_istimor.h"
#include "/d/Shire/bits.h"
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define TO this_object()
#define TP this_player()
#define LOG_SIZE       25000
#define NUM             sizeof(query_money_types(-1))

#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

create_room() {

    closed = CLOSED;

    set_short("Out on a limb of a large maple tree");
    set_long("You stand on a very long, strong branch of the "+
      "great maple tree, high above a hill below.  A rope "+
      "will let you down there, but the last few feet is "+
      "a drop, so it is impossible to climb back up.  There "+
      "is a sign affixed to the central trunk, and you notice "+
      "that this place is a great open space, perfect for "+
      "exercise.\n");

    add_item(({"branch","long strong branch","trunk"}),
      "This branch here is thin but incredibly strong, and leads back to "+
      "the central trunk which must be thirty feet across.\n");

    add_item(({"rope","hill","hill below"}),
      "The rope will let you drop down to the grassy hill below, where there "+
      "is a large stone obelisk.\n");

    add_item(({"maple tree","large maple tree","large tree"}),
      "You stand in the largest maple tree for miles around.\n");

    add_item("sign","It is firmly attached to the central trunk, and "+
      "can be read.\n");
    add_cmd_item("sign","read","Here you may learn skills taught by "+
      "the Heren Istimor.\n");


    add_prop(OBJ_S_WIZINFO, "@@wizinfo");


    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_exit(HEREN_ISTIMOR_DIR + "join","down",0,1);
    add_exit(HEREN_ISTIMOR_DIR + "board","northeast",0,1);
}


nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(HEREN_ISTIMOR_GUILD_LOG) > LOG_SIZE)
    {
	rename(HEREN_ISTIMOR_GUILD_LOG, (HEREN_ISTIMOR_GUILD_LOG + ".old"));
    }

    write_file(HEREN_ISTIMOR_GUILD_LOG, text);
}


wizinfo() {
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   /Igneous.\n");
}




void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_ip_number(ob) || !closed)
	return;

    if (ob->query_wiz_level())
	write("\n\nWARNING!\nYou shouldn't be here. "+
	  "I'm doing some work on the guild.\n");
    else {
	write("The guild is closed. Come back later.\n");
	ob->move("/d/Shire/guild/heren_istimor/join");
    }
}


init() {
    init_guild_support();
    init_skill_raise();
    ::init();
    add_action("do_improve","improve");
}

int
do_improve(string str)
{
    object player = this_player();

    if (!IS_MEMBER(player) && !player->query_wiz_level())
    {
	write("Hey, you're not a Heren Istimor!\n"+
	  "You should leave before a Vala sees you.\n");
	log_guild(ctime(time()) + " " + WRITE_NAME(player) +
	  " tried to train this skill: " + str + ".\n");
	return 1;
    }
}



close_guild() {
    if (closed) {
	closed = 0;
	return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

query_closed() { return closed; }


set_up_skills() {

    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_HERBALISM,      train_text(SS_HERBALISM),      0,0,50 );
    sk_add_train(SS_FORM_DIVINATION,  train_text(SS_FORM_DIVINATION),0,0,50);
    sk_add_train(SS_FORM_CONJURATION, train_text(SS_FORM_CONJURATION),0,0,50 );
    sk_add_train(SS_FORM_ABJURATION, train_text(SS_FORM_ABJURATION),0,0,50 );
    sk_add_train(SS_ELEMENT_LIFE,train_text(SS_ELEMENT_LIFE),0,0,50 );
    sk_add_train(SS_ELEMENT_EARTH,train_text(SS_ELEMENT_EARTH),0,0,50 );
    sk_add_train(SS_LANGUAGE,train_text(SS_LANGUAGE),0,0,50 );
    sk_add_train(SS_SPELLCRAFT,train_text(SS_SPELLCRAFT),0,0,50 );

}

train_text(skill) {
    string what;

    switch(skill) {
    case SS_HERBALISM:
	what="understand the use of herbs";
	break;
    case SS_FORM_DIVINATION:
	what="divine information from the Valar";
	break;
    case SS_FORM_CONJURATION:
	what="use the magic form conjuration";
	break;
    case SS_FORM_ABJURATION:
	what="use the magic form abjuration";
	break;
    case SS_ELEMENT_LIFE:
	what="perform magic in the element of life";
	break;
    case SS_ELEMENT_EARTH:
	what="perform magic in the earth element";
	break;
    case SS_LANGUAGE:
	what="understand different languages";
	break;
    case SS_SPELLCRAFT:
	what="perform general magic";
	break;
    }
    return what;
}
