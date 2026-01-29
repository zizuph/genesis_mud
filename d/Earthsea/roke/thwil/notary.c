#pragma strict_types

inherit "/d/Earthsea/roke/thwil/std/thwil_base_room";
inherit "/d/Genesis/notary/notary_service";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/notary/notary_service.h"

public void
create_thwil_room()
{
    string poster_text =
        "\nTen quick steps to Notarial Service usage:\n" +
        " 1. get form\n" +
        " 2. fill form title <document title>\n" +
        " 3. fill form type <contract|order|agreement|etc.>\n" +
        " 4. fill form access <private|guild|guildleader|public>\n" +
        " 5. fill form signers <signer name, ...>\n" +
        " 6. fill form contents\n" +
        " 7. submit form *\n" +
        " - The notary will check the form, and if everything is " +
        "   filled out correctly,\nyou will get a prepared document, " +
        "   which needs only to be signed.\n" +
        " 8. sign form [fully] [for <guild>]\n" +
        "     \"fully\" - will include your titles in signature,\n" +
        "     \"for <guild>\" will make you sign for one of the guilds\n" +
        "     you are a member of. See also \"help form access\"\n" +
        " 9. submit form *\n" +
        " - The submitted documents have a starting storage duration\n" +
        "   of 15 minutes, and can be extended by: \n" +
        "10. extend <document_number> for <period> *\n\n" +
        "* - service fees apply!!\n\n" +
        " Steps 2-6 and 8 can be done anywhere in the world,\n" +
        " as long as you carry the form.\n\n" +
        " See also: \"help notary\", \"help form\" and examine the index " +
        "in your inventory.\n\n";
    set_short("Archive of Genesis, Thwil branch");
    set_long("The Masters of Roke approved the construction " +
        "of this branch of the Archive of Genesis to further " +
        "the flow of reliable information amongst the Wizards " +
        "and those who wish to deal with them. A clerk " +
        "stands ready at the counter, waiting for you to take " +
        "a form from the bin. There is a poster behind " +
        "the clerk that you might be able to read.\n");
    add_item("bin", "A steel bin stands on the counter. " +
        "Upon examination it appears to contain blank notarial " +
        "forms that you can get and use for preparing documents.\n");
    add_item(({ "notary", "clerk" }),
        "The clerk is the local public notary. He is patiently " +
        "waiting to assist you with your business.\n");
    add_item("counter", "The simple wood counter is the only " +
        "notable feature of the room, holding only a plain sign " +
        "and a small steel bin which holds several blank forms. " +
        "The clerk is sitting behind the counter waiting for " +
        "you.\n");
    add_cmd_item("sign",({ "exa", "read" }), N_SIGN_TEXT);
    add_cmd_item("poster",({ "exa", "read" }), poster_text);
    add_exit("t4", "north");
}

public void
init()
{
    ::init();
    init_notary_service();
}

public void
leave_inv(object who, object to)
{
    ::leave_inv(who,to);
    leave_inv_notary(who,to);
}
