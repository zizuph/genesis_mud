 
/*     Training room for the hobbit guild.   */

/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

#pragma save_binary

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";
inherit "/d/Shire/lib/training";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "hobbit.h"

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

    set_short("Adventuresome Hobbits' Training Room");
    set_long("You have entered a rough smoke-filled room that is built from"
        + " a strange dark wood. Half of the floor is covered by a large"
        + " animal fur. The other half is plain hard wood. A soft fire"
        + " is crackling, merrily away in the corner. Meditating on the"
        + " comfortable fur is an old weathered hobbit. There is a small"
        + " sign on one of the walls.\n");


    add_item("fire","It is a fairly large in size. It serves to heat the "+
             "whole room. A lulling pop comes from the fire that seems "+
             "extremely relaxing.\n");

    add_item(({"wood","dark wood","strange dark wood"}),"It seems ancient yet "+
             "powerful. No hobbit has ever dared to vandalize this wood, and it "+
             "is very likey that none will.\n");
    add_item(({"animal fur","fur","large animal fur"}),"This fur is large enough "+
         "to cover fifteen hobbits! Certainly the creature it came from was a large "+
         "one.\n"
       + "Luckily you have never seen one such as this.\n");
    add_item(({"hobbit","old hobbit","old weathered hobbit"}),"Lines of age cover this "+
          "hobbit's face. He seems to be meditating, while smoking a brown pipe. "+
          "He can teach you individual skills, as well as make you more learned in "+
          "others. If you would kindly pay him, you may begin training right away. "+
          "Typing 'learn' will tell you what he can teach you that you do not already "+
          "know. Typing 'improve' will show you which skills he can and will continue "+
          "your training. Attacking this hobbit will bring pain to you, and shame to "+
          "our guild.\n");
    add_item(({"sign","small sign"}),"Amazingly enough it has words on it!\n");
    
    add_cmd_item("sign","read","This is the training room for the Adventuresome Hobbits.\n");
   add_cmd_item("hobbit","kill","@@kill");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop("_room_has_fire",1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

   add_exit(HOBGLD_DIR + "board","northeast",0,1);
   add_exit(HOBGLD_DIR + "start","northwest",0,1);
}


nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(HOBBIT_RACE_GUILD_LOG) > LOG_SIZE)
    {
	rename(HOBBIT_RACE_GUILD_LOG, (HOBBIT_RACE_GUILD_LOG + ".old"));
    }

    write_file(HOBBIT_RACE_GUILD_LOG, text);
}


wizinfo() {
   return ("If there should be due cause to close down the guild, do so by\n"+
           "typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a\n"+
           "reboot, the guild will be open by default. Please send me some\n"+
           "mail if there is anything that needs to be fixed.\n\n   /Igneous.\n");
}

kill()
{
write("As you begin to start at the hobbit, he quickly opens his eyes. Clearly he "+
      "very angry with you.\n"
    + "You begin to feel pain wracking through yur body.\n");
say(QCTNAME(TP)+" starts at the old meditating hobbit. The hobbit stands up and stares "+
           "stonily at the "+ TP->query_nonmet_name() +".\n");
   TP->command("choke");
   TP->command("puke");
   TP->command("cough painfully");
   TP->heal_hp(-60);
   return 1;
}


         
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else {
        write("The guild is closed. Come back later.\n");
        ob->move("/d/Shire/hobbit/join");
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

    if(!IS_MEMBER(player))
    {
      write("Hey, you're not an Adventuresome hobbit!\n"+
      "Get out of here before someone throws you out!\n");
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

    sk_add_train(SS_SNEAK,       train_text(SS_SNEAK),       0,0,50 );
    sk_add_train(SS_HIDE,        train_text(SS_HIDE),        0,0,50 );
    sk_add_train(SS_HERBALISM,   train_text(SS_HERBALISM),   0,0,50 );
    sk_add_train(SS_WEP_KNIFE,   train_text(SS_WEP_KNIFE),   0,0,50 );
    sk_add_train(SS_PICK_POCKET, train_text(SS_PICK_POCKET), 0,0,30 );


}

train_text(skill) {
    string what;

    switch(skill) {
        case SS_SNEAK:
            what="move while concealed";
            break;
        case SS_HIDE:
            what="conceal";
            break;
        case SS_HERBALISM:
            what="understand the use of herbs";
            break;
        case SS_WEP_KNIFE:
            what="use a knife skillfully";
            break;
        case SS_PICK_POCKET:
            what="lighten someone's load";
            break;
    }
    return what;
}
