inherit "/std/spells";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/LoD/spells/spells.h"
#include "/d/Terel/LoD/dungeon/quest.h"

#define MORE_OBJ        "/std/board/board_more"
#define KISSED_PEARL    "_live_i_kissed_necklace"
#define MAX_TIMES       15

/*
 * Global variables
 */

static int    ntimes, kissed;
static object cast_place;
static string spell_verb;

/*
 * Prototypes
 */
public void update_spells(object ob);
private string pad(string str, int z_length);
public int check_usage();
public void destroy_me();
public int allowed(object who);

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object
 */
public string
query_auto_load()
{
    if (check_usage() && ntimes)
        return MASTER + ":" + ntimes + "##" + kissed;
    else
        return "";
}

/*
 * Function name: init_arg
 * Description:   Called when autoloading
 */
public void
init_arg(string arg)
{
    sscanf(arg, "%d##%d", ntimes, kissed);
}

public int
allowed_to_kiss(object who)
{
    if (!who || !living(who))
        return 0;
        
    if (who->query_gender() == FEMALE && who->query_alignment() > 20)
        return 1;
        
    return 0;
}

public void
set_kissed()
{
    kissed = 1;
}

public int
check_usage()
{
    if (ntimes <= MAX_TIMES) return 1;
    return 0;
}

public int
do_kiss(string str)
{
    if (!str && str != "necklace" && str != "pearl" &&
        str != "black pearl") return 0;
    
    if (TP->query_prop(KISSED_PEARL)) {
        TP->catch_msg("Nothing in the world could make you " +
                      "kiss that " + short() + " again!\n");
        tell_room(ETP, QCTNAME(TP) + " refuses to kiss the " + short() +
                      ".\n", TP);
        if (ETO == TP)
            TP->command("$drop black necklace");
        return 1;
    }
    
    TP->catch_msg("You touch the pearl on the " + short() +
                  " with your lips.\n");
    tell_room(ETP, QCTNAME(TP) + " touches a " + short() + " with " +
              TP->query_possessive() + " lips.\n");
    
    if (allowed_to_kiss(TP) && kissed == 0) {
        TP->catch_msg("The pearl has a very bitter taste. You feel very " +
                      "uneasy.\n");
        TP->command("$cough");
        if (ETO == TP)
            TP->command("$drop black necklace");
        TP->add_panic(25);
        kissed = 1;
        TP->add_prop(KISSED_PEARL, 1);
    } else if (TP->query_alignment() < EVIL_LIM) {
        if (ntimes < MAX_TIMES - 2) {
           TP->catch_msg("The pearl has a sweet taste.\n");
        } else {
           TP->catch_msg("The pearl has lost most of its sweet taste.\n");
        }
    } else {
        TP->catch_msg("You feel nothing except a strange taste " +
                      " on your lips.\n");
    }
    return 1;
}

public int
do_force(string str)
{
    object *who, what;
    
    if (!what)
        return 0;
    
    notify_fail("Force who to do what?\n");
    
    if (!parse_command(str, all_inventory(ETP),
        "%l [to] 'kiss' %o", who, what))
        return 0;
        
    if (sizeof(who) != 2 || what != TO)
        return 0;
        
    if (!CAN_SEE(TP, TO))
        return 0;
        
    TP->catch_msg("You try to force " + QTNAME(who[1]) +
                  " to kiss the " + short() + ".\n");
    who[1]->catch_msg(QCTNAME(TP) + " tries to force you to kiss the " +
                      short() + ".\n");
    tell_room(ETP, QCTNAME(TP) + " tries to force " + QTNAME(who[1]) +
                   "to do something.\n", ({TP, who[1]}));
    
    if (TP->query_stat(SS_DIS)/2 > who[1]->query_stat(SS_DIS))
        who[1]->command("$kiss necklace");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_kiss, "kiss");
    if (ETO == ETP) {
        add_action(do_force, "force");
    }
}

public int
allowed(object who)
{
    if (interactive(who) && !kissed) return 0;
    if (who->query_alignment() < EVIL_LIM) return 1;
    return 0;
}

/*
 * Function name: update_spells
 * Description:   update the list of spells available to the player
 *                add spells via add_spell
 * Arguments:     ob - the player
 */
public void
update_spells(object ob)
{
    if (ob && allowed(ob))
    {
        add_spell("zargmon", "cast_spell", "Zasultra's Ice");
        add_spell("zarphus", "cast_spell", "Zasultra's Fire");
    }
}

/*
 * Function name: create_spells
 * Description:   Initialization function
 */
public void
create_spells()
{
   set_name("necklace");
   add_name(DQ_NECKLACE);
   set_adj("black");

   set_long("A necklace made of blackened silver. A black pearl has been " +
            "attached to it.\n");

   add_prop(OBJ_I_VALUE, 300 + random(50));
   add_prop(OBJ_I_WEIGHT, 28);
   add_prop(OBJ_I_VOLUME, 7);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_M_NO_STEAL, "@@check_steal");
   add_prop(OBJ_S_WIZINFO, "This necklace gives two spells to evil " +
                           "players. The object is autoloading but only " +
                           "as long as it hasn't been used more than " +
                           "a certain number (approx. 15) of times. " +
                           "Also, to use the spells, the evil player must " +
                           "first trick a 'good' female player into kissing " +
                           "the necklace.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"This is Zasultra's magical necklace.\n", 5,
          "If you are evil enough you may use it.\n", 15,
          "The powerful spells are called zarphus and zargmon.\n", 25,
          "To invoke the spells, however, you must first trick a " +
          "'good' female being into kissing the pearl. " +
          "And, remember, be quick to pick up the necklace " +
          "after the poor fool has kissed and dropped it. " +
          "She may not be fooled again that easily.\n", 35}));
          
   add_item(({"pearl", "black pearl"}), "@@my_pearl");
}

public int
check_steal()
{
    if (ETO->query_npc()) return 1;
    return 0;
}

public string
my_pearl()
{
   if (TP->query_skill(SS_AWARENESS) < 20)
       return "The black pearl looks valuable.\n";
   if (TP->query_alignment() > 650)
       return "The black pearl makes you feel uneasy. You get the feeling " +
              "that it contains black magic and should be destroyed.\n";
   if (TP->query_alignment() < EVIL_LIM) {
       if (!check_usage())
           return "The black pearl looks dull. Its powers seem gone.\n";
       if (kissed)
           return "The black pearl looks very dark and beautiful. You feel " +
                  "you can master its powers to their full extent.\n";
       else
           return "The black pearl looks somewhat dull, but you sense " +
                  "a great and beautiful power within it. You wonder " +
                  "what needs to be done with the pearl before you " +
                  "can invoke its dark powers.\n";
   }
   return "It looks valuable and you get a feeling it contains magic.\n";
}

public mixed
cast_spell(string str)
{
   string spell_file;

   
   if (cast_place != ETP)
       return "You lose your concentration on the spell due to " +
              "your rapid movement.\n";
              
   if (!check_usage()) {
       set_alarm(1.0, -1.0, destroy_me);
       return "The " + short() + " does not seem to respond.\n";
   }
   if (interactive(TP)) ntimes++;
   
   seteuid(getuid());
   spell_file = SPELL_DIR + spell_verb;
   return call_other(spell_file, spell_verb, str);
}

/*
 * Function name: query_spell_time
 * Description:   How long time will it take to cast a spell?
 * Arguments:     verb - The spell verb
 * Returns:       The time it will take. Real casting time will be time + 2
 */
public int
query_spell_time(string verb)
{
   spell_verb = verb;
   cast_place = ETP;
   return 0;
}

public void
enter_env(object new, object old)
{
   int i;
   object *all;
   
   ::enter_env(new, old);
   
   if (!new || !living(new)) return;
   
   all = all_inventory(new) - ({ TO });
   
   for (i=0; i<sizeof(all); i++)
   {
       if (MASTER == MASTER_OB(all[i]))
       {
           set_alarm(2.0, -1.0, destroy_me);
           break;
       }
   }
   
   update_spells(new);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
}

public void
destroy_me()
{
   if (ETO->query_prop(ROOM_I_IS))
      tell_room(ETO, "The " + short() + " vanishes.\n");
   else if (living(ETO))
      ETO->catch_msg("The " + short() + " vanishes.\n");
   remove_object();
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is typed.
 */
public void
list_spells()
{
   int i, i1, vsize, vlim, fold;
   string s1, s2;
   string text;

   if (!allowed(TP)) return;
   
   vsize = sizeof(verb_list);
   vlim = vsize;
   fold = vsize/2;
   if (vlim > fold) vlim = fold;
   if (vlim + fold == vsize - 1) {
      vlim++;
      fold++;
   }
   text = "------------------------***   Zasultra's Necklace  " +
          "***------------------------\n";

   for (i = 0; i < vlim; i++) {
      s1 = pad(verb_list[i], 15) + pad(name_list[i], 21);
      i1 = fold + i;
      if (vsize != vlim && i1 < vsize) {
         s2 = pad(verb_list[i1], 15) + name_list[i1];
         text += s1 + " | " + s2 + "\n";
      } else {
         text += s1 + " |\n";
      }
   }
   text += "-----------------------------------------------------" +
           "-------------------------\n";

   if (fold > TP->query_prop(PLAYER_I_MORE_LEN)) {
     seteuid(getuid());
     clone_object(MORE_OBJ)->more(text);
   } else {
     write(text);
   }
}

private string
pad(string str, int z_length)
{
   string space;

   space = "                                                 ";
   return str + extract(space, 0, z_length - strlen(str));
}

public int
query_spell_mess(string verb)
{
   write("You close your eyes momentarily as you touch the " +
         short() + ".\n");
   say(QCTNAME(TP) + " closes " + TP->query_possessive() +
       " eyes momentarily.\n");
   return 1;
}
