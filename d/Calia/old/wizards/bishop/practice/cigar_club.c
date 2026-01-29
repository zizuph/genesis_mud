/* This is just so the frog has a weapon */

inherit "/std/weapon";
#include "/sys/wa_types.h" 


public void
create_weapon()
{

    set_name("cigar");
    set_short("expensive cuban cigar");
    set_long("It's innocent-looking, but a deadly weapon in the" +
        " right hands\n");

    set_adj("expensive");
    set_adj("cuban");
    set_hit(40);
    set_pen(40);

    set_wt(W_CLUB); 
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH); 

}
