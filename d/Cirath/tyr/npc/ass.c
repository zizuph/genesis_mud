inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"
#define HAS_ASKED "_has_asked"

void
create_monster()
{
   ::create_monster();
  set_name("lim");
   set_race_name("half-elf");
   add_prop (LIVE_I_NEVERKNOWN, 1);
   set_adj("lanky");
   add_adj("shadowy");
    set_gender(0);
   set_long("At first you think this shadow draped person is a "
	+"human, but upon closer inspection, you realize he "
	+"is a half-elf.  Dressed in all black clothes, and moving "
	+"almost like a ghost through the small training hall, he "
	+"gives off an aura of darkness and evil.  He has a long cut on the "
	+"side of his face.  He is looking in "
	+"your direction with interest.\n"
	+"His eyes glow with dark knowledge.\n"
   +"He is a Soulknife of the Gray Reed Clan.\n");
   set_stats(({110,180,110,110,100,120}));
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_WEP_KNIFE, 100);
   set_skill(SS_PARRY, 60);
   set_skill(SS_2H_COMBAT, 75);
   set_skill(SS_HIDE,50);
   set_skill(SS_AWARENESS,50);

set_default_answer("The half-elf says: Interesting question.\n");
   set_act_time(6);
   add_act("grin");
   add_act("emote balances lightly on one foot before abruptly twisting "
	+"and slashing out with a knife.");
   add_act("emote scratches his arm.");
   add_act("emote leans against the far wall.");
   set_cact_time(3);
   add_cact("smile grimly");
   add_cact("emote rakes your head with his cold blackened dagger.");
   add_act("'I wish someone needed to have an accident.");
   add_act("'Boy she sure did put up a fight.  Scratched my face with those "
	+"damned manicured nails.");
   add_act("'You really should leave here.  You are not one of us.");
   add_cact("'If you run I will give you a five second headstart.");
   add_cact("'Your blood flows like wine.  When you are dead I will drink it.");
   add_cact("'You will die, now!");
  add_ask(({"murder","assassination"}),
   "@@ask_murder");
  add_ask(({"minthor","minthor house","Minthor House",
   "Minthor house","minthor House","minthors"}),
	"@@ask_minthor");
   add_ask("girl","@@ask_girl");

}

void
arm_me()
{
   object wep;
   seteuid(getuid(this_object()));
   clone_object(TYR_WEP+"ass_dagger")->move(TO);
   clone_object(TYR_ARM+"ass_armour")->move(TO);
    clone_object(TYR_ARM+"ass_cloak2")->move(TO);
   command("wield all");
   command("wear all");
   command("wear hood");
}

ask_murder()
{
    command("say Yeah thats the kind of thing I do.  I "
	+"know about all assassinations in the city. "
	+"You want to know about anyone in particular?\n");
    command("smile grimly");
    command("say This is a place of business, and you don't "
	+"look like a templar or some kind of crazy do gooder. "
	+"I'm proud of my work, and I've got nothing to hide. "
	+"Ask me the wrong thing, though, and I will gut you "
	+"like a pregnant mekillot.\n");
   return ">";
}

ask_minthor()
{
   command("say I remember that old broad.  Kind of a "
	+"simple job, but the pay was good.  That girl "
	+"paid me enough to take the rest of the year off.\n");
   command("sigh contentedly");
   return ">";
}

ask_girl()
{
   command("say You want to know who the girl was?  You're "
	+"getting a bit curious aren't you bud?\n");
   command("ponder");
   command("say Well okay, you look like the trustworthy sort. "
	+"She was one of the daughters in the house.  All I know "
	+"is her initials: MM.  If you can find out who that is, "
	+"then you know who paid me.\n");
   TP->add_prop(HAS_ASKED,1);
   return ">";
}

void
attacked_by(object ob)
{
   object enemy;
	::attacked_by(ob);
	set_alarm(5.0,0.0,"go_invis");
   
}

go_invis()
{
   write(query_The_name(TO) + " gasps in astonishment!\n"
	+query_The_name(TO) + " spins away from you and raises "
	+"the hood on his cloak.  He suddenly vanishes.\n");
	say(query_The_name(TO) + " gasps in astonishment!\n"
   +query_The_name(TO) + " spins away from you and raises "
	+"the hood on his cloak.  He suddenly vanishes.\n");
	TO->add_prop(OBJ_I_INVIS,3);
	set_alarm(120.0,0.0,"remove_invis");
}
remove_invis()
{
    TO->remove_prop(OBJ_I_INVIS);
     write(query_The_name(TO) + " appears suddenly in front of you, "
		+"lowering his hood around his shoulders.\n");
    say(query_The_name(TO) + " appears suddenly in front of you, "
	+"lowering his hood around his shoulders.\n");
}

/* ****************** Hamstring ************************* */

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    int slash;

    me=this_object();

    if(random(4)) return 0;

    hitresult = enemy->hit_me(350 + random(150), W_SLASH, me, -1);
    how = "lucky that the attack missed";
    slash = 0;
    if (hitresult[0] > 0)  { how = "barely wounded"; slash = 5; }
    if (hitresult[0] > 15) { how = "weakened"; slash = 10;  }
    if (hitresult[0] > 30) { how = "severely weakened"; slash = 15; }
    if (hitresult[0] > 50) { how = "hobbled"; slash = 20; }
    if (hitresult[0] > 75) { how = "crippled"; slash = 25; }

    enemy->catch_msg(QCTNAME(me) + " slashes at your hamstring with "+
                     HIS_HER(me) + " dagger.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" slashes at  "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " dagger.\n"+
                 QCTNAME(enemy)+" looks "+how+".\n",
                 me, enemy);
    if (slash>0)
{
   enemy->add_attack_delay(slash, 1);
   enemy->add_fatigue(-slash*5,1);
 }

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}


