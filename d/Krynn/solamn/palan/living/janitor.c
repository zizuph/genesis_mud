/* created by Aridor 06/19/93 */


#include "/ss_types.h"
#include "../local.h"

#define ROUTINE ({"e","gasp","shiver",   "n","sneeze","giggle",   \
  "w","cough","yodel",   "e","n","yawn",   "s","e","hiccup",   \
  "w","s","e",   "w","s","e",   "w","s","e",   "w","s","u",   \
  "w","burp","say Excuse me.",   "e","n","hmm",   "n","w","snarl",    \
  "e","finger all","laugh",   "n","ignore all","cackle",   \
  "n","stretch","stare",   "w","panic","sniff",   "e","n","poke all",   \
  "s","e","point all",   "w","s","e",   "s","grovel all","nod humbly",   \
  "w","s","e",   "w","s","d",    "e","u","smile char",   \
  "d","w","sigh",   "w","grin stu","gasp",   "e","n","cough",   \
  "w","yawn","shrug",   "e","n","stare",   "w","laugh wick","peer all",   \
  "e","n","w"})


inherit M_FILE

/* prototypes */
void clean_all_up(int num);


void
create_krynn_monster()
{
    int i;

    set_name("jan");
    add_name("janitor");
    set_living_name("janitor");
    set_race_name("human");
    set_adj("simple-minded");
    add_adj("looking");

    set_stats(({150,50,56,30,20,60}));
    set_hp(2000);

    i = 10 + random(30);
    set_alignment(i);
    set_knight_prestige(-i / 2);
    set_long("This is the janitor of the palace. His job is to keep "
	   + "everything tidy and clean.\n");

    set_alarm(1.0,0.0,"command","emote picks up his broom and bucket.");
    set_alarm(1.0,0.0,"command","emote arrives from his lunchbreak.");
    set_alarm(itof(sizeof(ROUTINE) * 9 + 40), 0.0, "go_back_to_lunch");
    clean_all_up(0);
}

void
go_back_to_lunch()
{
  seteuid(getuid(TO));
  command("emote puts his broom and bucket back.");
  command("emote gets out his lunch packet.");
  command("emote leaves for lunch.");
  TO->remove_object();
}

void
clean_all_up(int num)
{
    string com;
    int when = 0;
    int i, j;
    
    seteuid(getuid(this_object()));
    /*for(j = 0; j < sizeof(ROUTINE); j += 3)
      {*/
    when = 2;
    for(i = 0; i < 3; i++)
    {
	when += 2 + 2 * random(1);
	set_alarm(itof(when),0.0,"command", ROUTINE[num + i]);
    }
    set_alarm(itof(when + 2),0.0,"command", "say Everyone up with your feet!");
    set_alarm(itof(when + 10),0.0,"command", "get all");
    set_alarm(itof(when + 12),0.0,"command", "emote mops through the room.");
    set_alarm(itof(when + 14),0.0,"command", "emote smiles stupidly.");
    /*}*/
    if (num < sizeof(ROUTINE)-3)
      set_alarm(27.0, 0.0, "clean_all_up", num+3);
}
