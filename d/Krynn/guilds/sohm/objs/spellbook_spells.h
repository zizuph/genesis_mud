/*
 * The guild object for School of High Magic
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

string msg;

void
sohm_cantrip_spells()
{
   string cantrip_max_number = this_player()->query_cantrip_spells_max();

/*       THIS IS WHERE WE ADD CANTRIP LEVEL SPELLS TO THE SPELLBOOK        */

    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "CANTRIPS:", "* "+cantrip_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"kampiunarcanis_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kampiunarcanis *", "Read magic");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kampiunarcanis", "Read magic");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahhewa"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"ehtahhewa_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahhewa *", "Divine magus");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahhewa", "Divine magus");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"dotonobsule"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"dotonobsule_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "dotonobsule *", "Mirror portal");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "dotonobsule", "Mirror portal");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakarcanis"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"ickrakarcanis_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakarcanis *", "Detect magic");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakarcanis", "Detect magic");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"reskafar"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"reskafar_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reskafar *", "Dimensional rift");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reskafar", "Dimensional rift");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacovisp"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacovisp_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacovisp *", "Wind whisper");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacovisp", "Wind whisper");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"talkarpas"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"talkarpas_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "talkarpas *", "Wand light");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "talkarpas", "Wand light");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"riyitchikohk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"riyitchikohk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "riyitchikohk *", "Fool's curse");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "riyitchikohk", "Fool's curse");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ukrisrivek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ukrisrivek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ukrisrivek *", "Speak with dead");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ukrisrivek", "Speak with dead");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"jikmadakethend"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"jikmadakethend_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jikmadakethend *", "Shatter gemstones");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jikmadakethend", "Shatter gemstones");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"nuadealdoer"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"nuadealdoer_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nuadealdoer *", "Rune of welcome");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nuadealdoer", "Rune of welcome");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacotrekis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacotrekis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacotrekis *", "Wind gust");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacotrekis", "Wind gust");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"thirkualtiui"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"thirkualtiui_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkualtiui *", "Bird form");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkualtiui", "Bird form");

    msg += "\t ||||                              :                               |||| \n";

}

void
sohm_minor_spells()
{
   string minor_max_number = this_player()->query_minor_spells_max();

/*           THIS IS WHERE WE ADD MINOR LEVEL SPELLS TO THE SPELLBOOK        */

    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "MINOR SPELLS:", "* "+minor_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanfethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanfethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanfethos *", "Magic shield");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanfethos", "Magic shield");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanisvaes"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanisvaes_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanisvaes *", "Magic missile");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanisvaes", "Magic missile");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"apianak"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"apianak_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "apianak *", "Fire dart");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "apianak", "Fire dart");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"bakmadaingis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"bakmadaingis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "bakmadaingis *", "Prismatic spray");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "bakmadaingis", "Prismatic spray");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"uvelucavaes"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"uvelucavaes_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "uvelucavaes *", "Acid arrow");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "uvelucavaes", "Acid arrow");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"tonashingis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"tonashingis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashingis *", "Ballistic spray");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashingis", "Ballistic spray");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xarzithinloilfrey"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xarzithinloilfrey_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithinloilfrey *", "Ice shards");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithinloilfrey", "Ice shards");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"chikohk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"chikohk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "chikohk *", "Curse of uncertainty");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "chikohk", "Curse of uncertainty");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"wintektor"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"wintektor_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wintektor *", "Scare");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wintektor", "Scare");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"odenarcanis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"odenarcanis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "odenarcanis *", "Identify");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "odenarcanis", "Identify");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakfethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ickrakfethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakfethos *", "Detect resistances");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakfethos", "Detect resistances");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"okiai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"okiai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "okiai *", "Dazzle");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "okiai", "Dazzle");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"shirak"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"shirak_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shirak *", "Light");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shirak", "Light");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"wievaixen"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"wievaixen_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wievaixen *", "Fairie fire");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wievaixen", "Fairie fire");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothdraconis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothdraconis *", "Dragon fear protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothdraconis", "Dragon fear protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothocuir"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothocuir_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothocuir *", "Divination protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothocuir", "Divination protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ripeidronik"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ripeidronik_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ripeidronik *", "Blink");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ripeidronik", "Blink");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"nasirmitne"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"nasirmitne_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nasirmitne *", "Featherweight");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nasirmitne", "Featherweight");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"pabfrahrir"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"pabfrahrir_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "pabfrahrir *", "Water breathing");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "pabfrahrir", "Water breathing");


    msg += "\t ||||                              :                               |||| \n";

}

void
sohm_lesser_spells()
{
   string lesser_max_number = this_player()->query_lesser_spells_max();

/*          THIS IS WHERE WE ADD LESSER LEVEL SPELLS TO THE SPELLBOOK        */

    if(lesser_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "LESSER SPELLS:", "* "+lesser_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothixen"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothixen_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothixen *", "Fire protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothixen", "Fire protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothuvelucal"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothuvelucal_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothuvelucal *", "Acid protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothuvelucal", "Acid protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothgul"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothgul_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothgul *", "Cold protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothgul", "Cold protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothshochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothshochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothshochraos *", "Lightning protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothshochraos", "Lightning protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothweyog"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothweyog_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothweyog *", "Poison protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothweyog", "Poison protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ricindenthanus"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ricindenthanus_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ricindenthanus *", "Psychic blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ricindenthanus", "Psychic blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixenner"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixenner_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenner *", "Flame lance");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenner", "Flame lance");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarjikmada"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarjikmada_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarjikmada *", "Foreshock");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarjikmada", "Foreshock");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"shochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"shochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shochraos *", "Lightning bolt");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shochraos", "Lightning bolt");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"iniksuaco"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"iniksuaco_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "iniksuaco *", "Scouring wind");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "iniksuaco", "Scouring wind");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"skaerenpab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"skaerenpab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "skaerenpab *", "Geyser");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "skaerenpab", "Geyser");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xarzithnar"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xarzithnar_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithnar *", "Ice strike");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithnar", "Ice strike");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"levexlaraek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"levexlaraek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "levexlaraek *", "Enchant weapon");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "levexlaraek", "Enchant weapon");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixenchasid"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixenchasid_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenchasid *", "Flaming fist");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenchasid", "Flaming fist");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"hewavers"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"hewavers_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hewavers *", "Mage strength");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hewavers", "Mage strength");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kadenadon"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"kadenadon_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kadenadon *", "Blur");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kadenadon", "Blur");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"zhinpersvek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"zhinpersvek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "zhinpersvek *", "Shadow walk");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "zhinpersvek", "Shadow walk");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"sjachbuala"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"sjachbuala_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "sjachbuala *", "Shadow veil");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "sjachbuala", "Shadow veil");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahxiekiv"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ehtahxiekiv_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahxiekiv *", "Divine location");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahxiekiv", "Divine location");


    msg += "\t ||||                              :                               |||| \n";
    }

}

void
sohm_greater_spells()
{
   string greater_max_number = this_player()->query_greater_spells_max();


/*         THIS IS WHERE WE ADD GREATER LEVEL SPELLS TO THE SPELLBOOK        */

    if(greater_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "GREATER SPELLS:", "* "+greater_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"vistoma"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"vistoma_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "vistoma *", "True sight");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "vistoma", "True sight");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarmolik"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarmolik_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarmolik *", "Stoneskin");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarmolik", "Stoneskin");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"viraxregpos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"viraxregpos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "viraxregpos *", "Retributive ward");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "viraxregpos", "Retributive ward");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"temep"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"temep_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "temep *", "Haste");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "temep", "Haste");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xiekxilunwai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xiekxilunwai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xiekxilunwai *", "Portents and omens");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xiekxilunwai", "Portents and omens");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"whedabra"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"whedabra_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "whedabra *", "Gloom");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "whedabra", "Gloom");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"haddross"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"haddross_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "haddross *", "Gravity");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "haddross", "Gravity");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"reelojawa"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"reelojawa_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reelojawa *", "Dominate");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reelojawa", "Dominate");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanossalur"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanossalur_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanossalur *", "Teleport");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanossalur", "Teleport");

    msg += "\t ||||                              :                               |||| \n";
    }

}

void
sohm_advanced_spells()
{
   string advanced_max_number = this_player()->query_advanced_spells_max();

/*         THIS IS WHERE WE ADD ADVANCED LEVEL SPELLS TO THE SPELLBOOK        */

    if(advanced_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ADVANCED SPELLS:", "* "+advanced_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"virednith"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"virednith_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "virednith *", "Detonate");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "virednith", "Detonate");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarvirednith"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarvirednith_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarvirednith *", "Eruption");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarvirednith", "Eruption");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"hexlithdrevab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"hexlithdrevab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hexlithdrevab *", "Doom blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hexlithdrevab", "Doom blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ganimshochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ganimshochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ganimshochraos *", "Chain lightning");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ganimshochraos", "Chain lightning");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixengarmth"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixengarmth_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixengarmth *", "Fireball");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixengarmth", "Fireball");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"tonashkepesk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"tonashkepesk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashkepesk *", "Meteor storm");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashkepesk", "Meteor storm");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kepeskwiivai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"kepeskwiivai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kepeskwiivai *", "Storm fury");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kepeskwiivai", "Storm fury");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacodrevab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacodrevab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacodrevab *", "Cyclonic blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacodrevab", "Cyclonic blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"jennufethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"jennufethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jennufethos *", "Greater magic shield");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jennufethos", "Greater magic shield");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"plythusuiaerl"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"plythusuiaerl_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "plythusuiaerl *", "Arcane vulnerability");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "plythusuiaerl", "Arcane vulnerability");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"svihossalur"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"svihossalur_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "svihossalur *", "Teleport team");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "svihossalur", "Teleport team");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"thirkusio"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"thirkusio_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkusio *", "Polymorph self");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkusio", "Polymorph self");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trotharcanis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trotharcanis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trotharcanis *", "Magic protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trotharcanis", "Magic protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"welunyoweth"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"welunyoweth_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "welunyoweth *", "Stellar alignment");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "welunyoweth", "Stellar alignment");

    }

}

/* For redundancy as transition over to the new spellbook... can eventually delete */

string
read_cmd()
{
   string cantrip_max_number = this_player()->query_cantrip_spells_max();
   string minor_max_number = this_player()->query_minor_spells_max();
   string lesser_max_number = this_player()->query_lesser_spells_max();
   string greater_max_number = this_player()->query_greater_spells_max();
   string advanced_max_number = this_player()->query_advanced_spells_max();

   string guild_str;    

    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery") 
    {
        write("You are unable to decypher the magical runes " +
        "within the spellbook.\n");
        return "";
    }  

    if(this_player()->query_guild_name_occ() == "School of High Magic")
      guild_str = "sohm";
    else 
      guild_str = "wohs";

    say(QCTNAME(this_player()) + " opens " +this_player()->query_possessive()+ 
          " spellbook and begins studying the mystical runes within.\n");     
    write("You open your spellbook and examine the spells you have recorded within.\n");

    msg = "\n\n\t                     ~~**~~  Scribed Spells  ~~**~~                    \n"+
"\t     _____________________________   ______________________________ \n"+
"\t .-/|            ~~**~~           \\ /              ~~**~~          |\\-. \n"+
"\t ||||                              :                               |||| \n"+
"\t ||||   Spell:                     :    Description:               |||| \n"+
"\t ||||                              :                               |||| \n";

/*       THIS IS WHERE WE ADD CANTRIP LEVEL SPELLS TO THE SPELLBOOK        */

    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "CANTRIPS:", "* "+cantrip_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"kampiunarcanis_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kampiunarcanis *", "Read magic");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kampiunarcanis", "Read magic");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahhewa"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"ehtahhewa_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahhewa *", "Divine magus");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahhewa", "Divine magus");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"dotonobsule"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"dotonobsule_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "dotonobsule *", "Mirror portal");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "dotonobsule", "Mirror portal");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakarcanis"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"ickrakarcanis_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakarcanis *", "Detect magic");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakarcanis", "Detect magic");
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacovisp"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacovisp_memorised"))
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacovisp *", "Wind whisper");
       else
         msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacovisp", "Wind whisper");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"talkarpas"))
    {
       if(SOHM_MANAGER->query_memorised_spell(this_player(),"talkarpas_memorised"))
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "talkarpas *", "Wand light");
       else
          msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "talkarpas", "Wand light");
    }
    else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "................", "................");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"riyitchikohk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"riyitchikohk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "riyitchikohk *", "Fool's curse");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "riyitchikohk", "Fool's curse");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ukrisrivek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ukrisrivek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ukrisrivek *", "Speak with dead");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ukrisrivek", "Speak with dead");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"jikmadakethend"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"jikmadakethend_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jikmadakethend *", "Shatter gemstones");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jikmadakethend", "Shatter gemstones");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"nuadealdoer"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"nuadealdoer_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nuadealdoer *", "Rune of welcome");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nuadealdoer", "Rune of welcome");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacotrekis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacotrekis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacotrekis *", "Wind gust");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacotrekis", "Wind gust");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"thirkualtiui"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"thirkualtiui_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkualtiui *", "Bird form");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkualtiui", "Bird form");

    msg += "\t ||||                              :                               |||| \n";


/*           THIS IS WHERE WE ADD MINOR LEVEL SPELLS TO THE SPELLBOOK        */

    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "MINOR SPELLS:", "* "+minor_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanfethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanfethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanfethos *", "Magic shield");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanfethos", "Magic shield");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanisvaes"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanisvaes_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanisvaes *", "Magic missile");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanisvaes", "Magic missile");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"apianak"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"apianak_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "apianak *", "Fire dart");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "apianak", "Fire dart");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"bakmadaingis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"bakmadaingis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "bakmadaingis *", "Prismatic spray");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "bakmadaingis", "Prismatic spray");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"uvelucavaes"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"uvelucavaes_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "uvelucavaes *", "Acid arrow");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "uvelucavaes", "Acid arrow");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"tonashingis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"tonashingis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashingis *", "Ballistic spray");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashingis", "Ballistic spray");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xarzithinloilfrey"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xarzithinloilfrey_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithinloilfrey *", "Ice shards");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithinloilfrey", "Ice shards");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"chikohk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"chikohk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "chikohk *", "Curse of uncertainty");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "chikohk", "Curse of uncertainty");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"wintektor"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"wintektor_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wintektor *", "Scare");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wintektor", "Scare");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"odenarcanis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"odenarcanis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "odenarcanis *", "Identify");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "odenarcanis", "Identify");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakfethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ickrakfethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakfethos *", "Detect resistances");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ickrakfethos", "Detect resistances");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"okiai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"okiai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "okiai *", "Dazzle");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "okiai", "Dazzle");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"shirak"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"shirak_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shirak *", "Light");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shirak", "Light");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"wievaixen"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"wievaixen_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wievaixen *", "Fairie fire");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "wievaixen", "Fairie fire");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothdraconis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothdraconis *", "Dragon fear protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothdraconis", "Dragon fear protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothocuir"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothocuir_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothocuir *", "Divination protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothocuir", "Divination protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ripeidronik"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ripeidronik_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ripeidronik *", "Blink");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ripeidronik", "Blink");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"nasirmitne"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"nasirmitne_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nasirmitne *", "Featherweight");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "nasirmitne", "Featherweight");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"pabfrahrir"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"pabfrahrir_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "pabfrahrir *", "Water breathing");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "pabfrahrir", "Water breathing");


    msg += "\t ||||                              :                               |||| \n";



/*          THIS IS WHERE WE ADD LESSER LEVEL SPELLS TO THE SPELLBOOK        */

    if(lesser_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "LESSER SPELLS:", "* "+lesser_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothixen"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothixen_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothixen *", "Fire protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothixen", "Fire protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothuvelucal"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothuvelucal_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothuvelucal *", "Acid protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothuvelucal", "Acid protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothgul"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothgul_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothgul *", "Cold protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothgul", "Cold protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothshochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothshochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothshochraos *", "Lightning protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothshochraos", "Lightning protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothweyog"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trothweyog_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothweyog *", "Poison protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trothweyog", "Poison protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ricindenthanus"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ricindenthanus_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ricindenthanus *", "Psychic blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ricindenthanus", "Psychic blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixenner"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixenner_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenner *", "Flame lance");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenner", "Flame lance");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarjikmada"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarjikmada_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarjikmada *", "Foreshock");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarjikmada", "Foreshock");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"shochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"shochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shochraos *", "Lightning bolt");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "shochraos", "Lightning bolt");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"iniksuaco"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"iniksuaco_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "iniksuaco *", "Scouring wind");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "iniksuaco", "Scouring wind");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"skaerenpab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"skaerenpab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "skaerenpab *", "Geyser");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "skaerenpab", "Geyser");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xarzithnar"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xarzithnar_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithnar *", "Ice strike");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xarzithnar", "Ice strike");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"levexlaraek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"levexlaraek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "levexlaraek *", "Enchant weapon");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "levexlaraek", "Enchant weapon");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixenchasid"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixenchasid_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenchasid *", "Flaming fist");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixenchasid", "Flaming fist");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"hewavers"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"hewavers_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hewavers *", "Mage strength");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hewavers", "Mage strength");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kadenadon"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"kadenadon_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kadenadon *", "Blur");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kadenadon", "Blur");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"zhinpersvek"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"zhinpersvek_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "zhinpersvek *", "Shadow walk");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "zhinpersvek", "Shadow walk");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"sjachbuala"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"sjachbuala_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "sjachbuala *", "Shadow veil");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "sjachbuala", "Shadow veil");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahxiekiv"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ehtahxiekiv_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahxiekiv *", "Divine location");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ehtahxiekiv", "Divine location");


    msg += "\t ||||                              :                               |||| \n";
    }


/*         THIS IS WHERE WE ADD GREATER LEVEL SPELLS TO THE SPELLBOOK        */

    if(greater_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "GREATER SPELLS:", "* "+greater_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"vistoma"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"vistoma_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "vistoma *", "True sight");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "vistoma", "True sight");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarmolik"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarmolik_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarmolik *", "Stoneskin");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarmolik", "Stoneskin");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"viraxregpos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"viraxregpos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "viraxregpos *", "Retributive ward");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "viraxregpos", "Retributive ward");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"temep"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"temep_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "temep *", "Haste");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "temep", "Haste");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"xiekxilunwai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"xiekxilunwai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xiekxilunwai *", "Portents and omens");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "xiekxilunwai", "Portents and omens");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"whedabra"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"whedabra_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "whedabra *", "Gloom");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "whedabra", "Gloom");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"haddross"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"haddross_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "haddross *", "Gravity");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "haddross", "Gravity");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"reelojawa"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"reelojawa_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reelojawa *", "Dominate");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "reelojawa", "Dominate");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanossalur"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"arcanossalur_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanossalur *", "Teleport");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "arcanossalur", "Teleport");

    msg += "\t ||||                              :                               |||| \n";
    }

/*         THIS IS WHERE WE ADD ADVANCED LEVEL SPELLS TO THE SPELLBOOK        */

    if(advanced_max_number > 0)
    {
    msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ADVANCED SPELLS:", "* "+greater_max_number+
                   " can be memorised *");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"virednith"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"virednith_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "virednith *", "Detonate");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "virednith", "Detonate");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"edarvirednith"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"edarvirednith_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarvirednith *", "Eruption");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "edarvirednith", "Eruption");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"hexlithdrevab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"hexlithdrevab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hexlithdrevab *", "Doom blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "hexlithdrevab", "Doom blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ganimshochraos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ganimshochraos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ganimshochraos *", "Chain lightning");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ganimshochraos", "Chain lightning");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ixengarmth"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"ixengarmth_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixengarmth *", "Fireball");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "ixengarmth", "Fireball");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"tonashkepesk"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"tonashkepesk_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashkepesk *", "Meteor storm");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "tonashkepesk", "Meteor storm");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"kepeskwiivai"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"kepeskwiivai_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kepeskwiivai *", "Storm fury");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "kepeskwiivai", "Storm fury");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"suacodrevab"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"suacodrevab_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacodrevab *", "Cyclonic blast");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "suacodrevab", "Cyclonic blast");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"jennufethos"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"jennufethos_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jennufethos *", "Greater magic shield");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "jennufethos", "Greater magic shield");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"plythusuiaerl"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"plythusuiaerl_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "plythusuiaerl *", "Arcane vulnerability");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "plythusuiaerl", "Arcane vulnerability");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"svihossalur"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"svihossalur_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "svihossalur *", "Teleport team");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "svihossalur", "Teleport team");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"thirkusio"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"thirkusio_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkusio *", "Polymorph self");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "thirkusio", "Polymorph self");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trotharcanis"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"trotharcanis_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trotharcanis *", "Magic protection");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "trotharcanis", "Magic protection");

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"welunyoweth"))
      if(SOHM_MANAGER->query_memorised_spell(this_player(),"welunyoweth_memorised"))
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "welunyoweth *", "Stellar alignment");
      else
        msg += sprintf("\t ||||   %-26s :    %-26s |||| \n", "welunyoweth", "Stellar alignment");

    }
    
    msg +=
"\t ||||                              :                               |||| \n"+
"\t ||||                              :                               |||| \n"+
"\t ||||_____________________________ : ______________________________|||| \n"+
"\t |||/=============================\\:/==============================\\||| \n"+
"\t `-------------------------------~___~--------------------------------' \n\n" +
"\t     For details about each scribed spell check help " +guild_str+ " <spell>.       \n\n"+
"\t     Spells memorised are listed in this spellbook with an *.            \n"+
"\t     For a list of memorised spells use the 'spells' command.            \n";

    write( msg );

    return "";
}
