inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/introfnc.h"

create_monster()
{
    set_name("norad");
    set_title("The Scribe of Altaruk");
    set_race_name("dwarf");
    set_adj("flimsy");
    add_adj("informative");
    set_gender(1);
    set_long("She is the scribe of Altaruk. She knows about" +
        " all that is to know about athasian laws and " +
        " society. Maybe you should ask her for info?\n");
    set_alignment(250);
    set_stats(({100,110,100,75,75,100}));
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,100);
    set_act_time(12);
    add_act("say Can I help you?.");
    add_act("mumble");
    add_act("scratch");
    add_act("smile");
    add_act("wistle");
    set_cact_time(6);
    add_cact("say Help!");
    add_cact("say IT'S KILLING ME! ARG!!");
    add_cact("say Eeeeek!");
    add_cact("cower");
    add_ask("friend", "Ehh.. I have no time for friends." +
        " To much to do.\n");
    add_ask("room", "There is an inn near here. Ask there.\n");
    add_ask(({"favor","help","task"}),"If you want employment you" +
        " try at the barracks.\n");
        
    add_ask(({"info","information"}),"I have information on these" +
    " subjects:\n  Calender\n  Altaruk\n  Caravans\n");
    
    add_ask("calender","Every city state has its own calendar, but that most" +
    " commonly used and considered the Calendar of Tyr. The Tyr calender uses" +
    " two cycles that make up the year names. One cycle has eleven names while" +
    " the other has seven.\n" +
    " Ral       Fury\n friend    Contemplation\n Desert    Vengeance\n" +
    " Priest    Slumber\n Wind      Defiance\n Dragon    Reverence\n" +
    " Mountain  Agitation\n King\n Silt\n Guthay\n" +
    " The cycles come to an end after 77 years. This is called a Kings age.\n" +
    " we are now in the 183. Kings Age." +
    " The year has three phases or months if you please. " +
    " High Sun, Descending Sun and Ascending Sun. Each are 124 days long making" +
    " the year 372 days.\n");
    
    add_ask("altaruk","Altaruk is a client town of the merchant houses of Wavir," +
    " Rees, and Tomblador. Thay are based in the city of Balic. Other merchant" +
    " houses must pay toll for their caravans to pass through. The garrison counts" +
    " five hundred mercenaries. This contingent of warriors is commanded by" +
    " Arisphistaneles. Due to him preservers are welcome in Altaruk. Defilers are" +
    " not.\n");
    
    add_ask("caravans","As a caravan office has opened I feel its better for you" +
    " go there for information on that.\n");

   add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
 
}
