inherit "/std/domain_link";

void
create_domain()
{
    /* Neccesary for the mortal last command */
    add_preload("/sys/global/time");
    
    /* Beginner files */
    add_preload("/d/Genesis/login/bodies");

    /* Wiz_quest central */
    add_preload("/d/Genesis/obj/wizquest/mage_central");

    /* The circle line ship */
    add_preload("/d/Genesis/start/human/town/pier4");

    /* The master of the delivery offices. */
    add_preload("/d/Genesis/delivery/master");

    /* The fury of Genesis. */
    add_preload("/d/Genesis/wiz/fury");

    /* Logs
    */
    rm("/d/Genesis/start/human/log/roach_log");


}
