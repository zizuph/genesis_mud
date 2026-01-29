#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/std/act/action.c";
inherit AM_FILE
object obj;

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("dawn");
    set_living_name("dawn");
    set_race_name("elf");
    set_title("the Seer");
    set_adj("young");
    add_adj("white-haired");
    set_long("This female elf is dressed in a bright robe, and her face "+
             "is covered in a silk scarf. The scarf hides her features "+
             "you manage to see some young eyes staring at you.\n");
    
    set_stats(({60,80,30,60,50,40}));
    set_alignment(500);
    set_gender(1);

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000); 
    set_introduce(1);
    add_ask(" [about] 'fortune'", "say Yes, I might be able to "+
      "tell your fortune, just give me a gold coin.", 1);
    add_ask(" [about] 'future'", "say Yes, I might be able to "+
      "tell your future, just give me a gold coin.", 1);
    add_ask(" [about] 'crystal'", "say I use the crystal ball to "+
      "see the future.", 1);
    add_ask(" [about] 'ball'", "say I use the crystal ball to "+
      "see the future.", 1);
    add_ask(({"task","quest","job","herb"}), VBFC_ME("quest_hint"));
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    clone_object(MARM + "silk_scarf.c")->move(this_object(),1);
    clone_object(MARM + "robe1.c")->move(this_object(),1);
    command("wear all");
}

string
quest_hint()
{
    if(TP->test_bit("ansalon",0,2))
    {
	TO->command("say Sorry, I have no jobs for you "+
	  "at present.");
	return "";
    }
    TO->command("hmm");
    TO->command("say I sometimes search for herbs in the forest "+
                "south of here. I don't normaly find anything interesting, "+
                "but yesterday I found a strange herb, that've never seen "+
                "before.");
    TO->command("say A friend of mine has taken up residence in the forest "+
                "there. Her name is Laran and her hut is well camouflaged "+
                "so you properly haven't seen it yet.");
    TO->command("smile");
    TO->command("say Find the hut and give the herb to her. She'll know what "+
                "it is, and she might even use it to make one of her special "+
                "brews.");
    setuid();
    seteuid(getuid());
    obj = clone_object("/d/Ansalon/goodlund/nethosak/city/obj/comfrey");
    obj->move(TP,1);
    TP->tell_watcher("Dawn gives "+ QTNAME(TP) + " a dark-green leaf.\n");
    TP->catch_msg("Dawn gives you a dark-green leaf.\n");
    return "";
}