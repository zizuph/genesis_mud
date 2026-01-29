/* created by Aridor, 03/10/94 */
/* Edited by Navarre, June 11th 2006
 * Bribe command without arguments caused runtime error.
 */

#include "../local.h"
inherit M_FILE
#include <macros.h>
#include <money.h>
#include <cmdparse.h>

/*prototype*/
void arm_me();

int good = 0;

void
create_theiwar()
{
    set_adj("scared");
}

nomask void
create_krynn_monster()
{
    set_name("theiwar");
    add_adj("dark");
    set_gender(0);
    set_short("@@query_adjects@@ dwarf");
    set_pshort("@@query_adjects@@ dwarves");
    set_long("This is a @@query_adjects@@ dwarf. The expression on his face " +
         "lets you think this guy must have been here under this " +
         "mountain all his life. He looks just as hard as the rock " +
         "around him.\n");
    set_race_name("dwarf");
    default_config_mobile(20);
    set_all_attack_unarmed(10, 10);
    set_all_hitloc_unarmed(5);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_alignment(-random(20) - 5);
    set_knight_prestige(40);

    NEVERKNOWN;
    add_act("say Without a map, you're lost around here.");
    add_act("emote grumbles something into his beard.");
    add_act("say Hmmm, haven't been to our treasury in a while, seems no " +
        "one has enough to live these days let alone save some.");

    add_ask("[about] [quest] 'master'",
        "say I haven't seen the Quest Master in a while, no idea where " +
        "he hides out these days.",1);
    add_ask("[about] 'spectacles' / 'glasses'",
        "say I haven't seen any. Guess you'll have to look around " +
        "yourself if you need to find some.",1);
    add_ask("[about] 'map' / 'mapping'",
        "say Make one, and you won't get lost!",1);
    add_ask("[about] 'theiwar' / 'dwarf' / 'dwarves'",
        "say Yea, that's us.",1);
    add_ask("[about] 'thief' / 'thieves'",
        "say Thieves?!? Fortunately I've never seen any, I'd kill'em " +
        "without thinking twice.",1);
    add_ask("[about] 'treasury'",
        "say It's well hidden! No one is ever going to find it!    Oh " +
        "well, it's empty anyway these days I reckon, our mines are " +
        "pretty much exhausted.",1);
    add_ask("[about] 'mine' / 'mines' / 'gold' / 'silver' / 'iron'",
        "say We used to have that in abundance, it's just our mines " +
        "are nearing exhaustion now. No need to even put anything " +
        "in the treasury now anymore.",1);
    add_ask(" [about] [iron] [silver] [gold]", "say Our mines " +
        "are almost exhausted now, but if we are lucky we might still find " +
        "some pieces of gold or silver, most often its iron though.", 1);
    add_ask(" [about] 'carbon'", "say Aye, from time to time we find some " +
        "pieces of carbon here, we sell it to the smith though. He'd like " +
        "to buy our silver and gold too... but that goes to the treasury...", 1);

    create_theiwar();

    set_alarm(2.0,0.0,"arm_me");

}


void
arm_me()
{
  seteuid(getuid(TO));
  MONEY_MAKE(random(1),"gold")->move(TO);
  clone_object(OBJ + "miniaxe")->move(TO);

  command("wield all");
}


string
query_adjects()
{
  return query_adjs()[0] + " " + query_adjs()[1];
}

void
make_good()
{
    if (good)
      return;
    good = 1;
    remove_adj("scared");
    remove_adj("dark");
    set_adj("small");
    add_adj("friendly");
    set_long("This is a @@query_adjects@@ dwarf. From the expression on his face " +
         "you wouldn't think this guy has been here under this " +
         "mountain all his life. He looks friendly and has a merry twinkle in " +
         "his eyes, blinking at you from above his beard.\n");
    set_alignment(random(20) + 5);
    set_knight_prestige(-1);
    command("emote cheers up visibly as his aura shifts from dark to light.");
    command("smile");
}

void
make_evil()
{
    if (!good)
      return;
    good = 0;
    remove_adj("small");
    remove_adj("friendly");
    set_adj("scared");
    add_adj("dark");
    set_long("This is a @@query_adjects@@ dwarf. The expression on his face " +
         "lets you think this guy must have been here under this " +
         "mountain all his life. He looks just as hard as the rock " +
         "around him, probably even harder!\n");
    set_alignment(-random(20) - 5);
    set_knight_prestige(40);
    command("emote moans and chokes back a scream as his aura shifts from light to dark.");
    command("grin evil");
}

void
init_living()
{
    add_action("bribe","bribe");
    add_action("threaten","threaten");
}

int
bribe(string str)
{
    string str1,str2;
    int i;
    object thing;
    object *tmp;

    if(strlen(str)==0)
    {
      NF("Bribe who with what?\n");
      return 0;
    }
    NF("Bribe who with what?\n");
    i = sscanf(str,"%s with %s",str1,str2);
    if (i != 2)
      return 0;
    if (!id(str1))
      return 0;
//  Fixed by plarry, gives a runtime error if they don't have the item
//  they are trying to bribe with. 4/26/96.
//    thing = FIND_STR_IN_OBJECT(str2,TP)[0];
//    NF("You don't have the " + str2 + ".\n");
    NF("You don't have the " + str2 + ".\n");
    if(!sizeof(tmp = FIND_STR_IN_OBJECT(str2,TP)))
       return 0;
    thing = tmp[0];
//  thing now guaranteed to exist. - Pl
//    if (!thing)
//      return 0;
    write("You try to bribe the dwarf with the " + str2 + ".\n");
    thing->move(TO);
    if (thing->query_value() > 1500)
      command("say Ah, how wonderful! I'll tell ya a secret for this: Our treasury is " +
          "reachable from the turnable rooms.");
    if (thing->query_value() > 2000)
      command("say And here's the trick: You have to look for it all by yourself!");
    return 1;
}

int
threaten(string str)
{
    NF("What?\n");
    if (!id(str))
      return 0;
    write("You threaten the dwarf.\n");
    command("say I'm not gonna say anything!");
    return 1;
}
