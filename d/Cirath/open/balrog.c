inherit "/std/monster";
#include "/d/Shire/defs.h";
int resist;  // The value of resistment

void
create_monster()
{

    if (!IS_CLONE)
        return;

    set_race_name("Balrog of Moria");
    set_name("Balrog of Moria");
   // set_adj("demon");
    add_name("balrog");
    set_short("massive fire-cloaked balrog");
    set_long("Before you stands one of the single most feared creatures "
    +"in Middle Earth.  What was once a being that embraced the light "
    +"has now become a creature of darkness, flames, and pain.  "
    +"Standing roughly 3 meters tall, the creature's body is almost "
    +"completely hidden by the shadows it seems to wear as cloth, but "
    +"the chaotic licking of the fire across and around its body is "
    +"enough for you to see its long, heavily muscled limbs.  Just the "
    +"sight of this beast is enough to make your frail heart skip "
    +"a beat.\n");
    set_gender(2);
    set_all_hitloc_unarmed(60);
    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 3000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(MAGIC_I_RES_MAGIC,100);
    add_prop(MAGIC_I_RES_DEATH,100);
    add_prop(MAGIC_I_RES_LIFE,100);
    add_prop(MAGIC_I_RES_LIGHT,100);
    add_prop(MAGIC_I_RES_WATER,50);
    add_prop(MAGIC_I_RES_AIR,100);
    add_prop(MAGIC_I_RES_EARTH,100);
    add_prop(MAGIC_I_RES_FIRE,100);
    add_prop(MAGIC_I_RES_POISON,90);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_LIFE,  100);
    add_prop(OBJ_I_RES_LIGHT, 100);
    add_prop(OBJ_I_RES_WATER, 50);
    add_prop(OBJ_I_RES_AIR,   100);
    add_prop(OBJ_I_RES_EARTH, 100);
    add_prop(OBJ_I_RES_FIRE,  100);
    add_prop(OBJ_I_RES_COLD,  100);
    add_prop(OBJ_I_RES_POISON, 90);
    set_stats(({350,350,390,260,265,250}));
    set_alignment(-1200);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want your crap!\n");
    add_prop(LIVE_I_SEE_DARK,1000);
    add_prop(LIVE_I_SEE_INVIS,1000);
    add_prop(LIVE_I_QUICKNESS,300);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_LANGUAGE, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH,100);
    set_skill(SS_ELEMENT_WATER,100);
    set_skill(SS_ELEMENT_LIFE,100);
    set_skill(SS_ELEMENT_DEATH,100);
    set_skill(SS_FORM_CONJURATION,100);
    set_skill(SS_FORM_ABJURATION,100);
    set_skill(SS_FORM_TRANSMUTATION,100);

    set_knight_prestige(10000);

    set_act_time(5);
    /* do_speak will make the npc talk their own language */
    add_act("emote eyes burn with scorching flame as it "
    +"surveys the room.");
    add_act("'It has been too long since I had fresh meat, I'm "
    +"glad you came.\n");
    set_cact_time(5);
    add_cact("emote roars with unbridled fury.");
    add_cact("emote attempts to punch you in the face with its "
    +"massive flaming greatsword.");

    set_alarm(0.5, 0.0, "arm_me");

}

void
attacked_by(object ob)
{
    find_player("bolg")->catch_msg(ob->query_real_name() +
         " is fighting the Balrog of Moria.\n");
//    command("slap " + ob->query_real_name());
//    command("steal coins from " + ob->query_real_name());
  ::attacked_by(ob);

}

void
react_to_intro(string who,string garbage)
{
    command("say Am I supposed to be impressed little one?");
    set_alarm(0.2,0.0,"scream","Die!!",who);
}

void
arm_me()
{
    object wep;

    seteuid(getuid(TO));


    wep = clone_object("/d/Shire/moria/wep/balrog_whip");
    wep->move(TO);
    wep = clone_object("/d/Shire/moria/wep/balrog_sword");
    wep->move(TO);

    command("wield all");

    make_cash((random(13)+5), "gold");
    make_cash((random(20)+18), "platinum");
}

resist()
{
   if(resist)
      write("The Balrog closes its eyes for a moment, and you "
      +"see its wounds instantly regenerate.\n");
   this_object()->add_hp(resist);
}

void
cr_got_hit(int hid, int ph, object att,int aid, int dt, int dam)
{
   resist=dam/2;
   ::cr_got_hit();
   set_alarm(0.1,0.0,"resist");
   return;
}


int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = this_object();


    if(random(8)) return 0;
    {
        ob =  FILTER_LIVE(all_inventory(environment(TO))) - ({ TO });

        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 500 + random(350);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, TO, -1);

                        how = "without";
            if (hitresult[0] > 0)
                how == "barely";
            if (hitresult[0] > 10)
                how = "slightly";
            if (hitresult[0] > 20)
                how = "badly";
            if (hitresult[0] > 40)
                how = "very badly";
            if (hitresult[0] > 60)
                how = "horribly";
            ob[i]->catch_msg("The Balrog grins cruelly, then with "
            +"a lift of its arms, flame erupts all around you!\n");
            ob[i]->catch_msg("The fire sears the air around you, "+ how +
                " burning you!\n");


            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }
}

public void
do_die(object killer)
{
    killer->set_bit(1,15);

    ::do_die(killer);
}


