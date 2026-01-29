#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");

    set_long("   The forest here is much different than the rest. The trees "+
             "are much, much smaller. Some of the treetops are actually "+
             "visible even through the thick mist which covers this entire "+
             "wood. The path has been cleared of vines recently, by someone "+
             "or somethign with a blade. The trees bend over the path here, "+
             "but here it almost feels as if the trees are sheltering or "+
             "protecting the contents of the path. This path continues under "+
             "the small trees and through the mist to the southeast. There "+
             "is a small opening between two trees to the northwest.\n\n");
    add_fexit(CORAMAR+"f18", "northwest", 1);
    add_fexit(CORAMAR+"f69", "southeast", 0);
}
