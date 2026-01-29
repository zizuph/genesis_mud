/*
 * News Server for Sparkle
 *
 * This will handle Club, Guild well all news, information and so on.
 *
 * Mapping
 *
 * ([ target (The target, actors, monks, mercs) :
 *   ({ postdata (The actual news post),
 *      postowner (The poster, mortal or wizard, query_real_name()),
 *      postdate (The date in INT 20060101),
 *   })
 * ])
 *
 * Lunatari 2006
 */
#pragma no_clone
#pragma strict_types

#include "defs.h"

#define SPARKLE_NEWS (S_DOMAIN_VAR_DIR + "news_mapping")

mapping news;

void
restore_mapping()
{
    news = ([ ]);

    news = restore_map(SPARKLE_NEWS);    
}

void
save_mapping()
{
    save_map(news, SPARKLE_NEWS);
}

int
add_news(string target, string post, string name, int date)
{
    mixed *temp;
    int   size;

    temp = ({ post, name, date, });

    if(!news[target]) news[target] = ([ ]);

    size = (sizeof(m_indexes(news[target])))+1;

    news[target][size] = temp;

    save_mapping();

    return 1;
}

int
remove_news(string target, int number)
{

    if(!news[target])
	return 0;

    if(!number)
    {
	news = m_delete(news, target);
	return 1;
    }

    if(!news[target][number])
	return 0;

    news[target] = m_delete(news[target], number);

    return 1;
}

mixed
query_news(string target, int number)
{

    if(!news[target])
	return 0;

    if(!number)
      return news[target];
    
    if(!news[target][number])
	return 0;

    return news[target][number];
}

mapping
list_news()
{
    return news;
}

public void
create()
{
    setuid();
    seteuid(getuid());

    restore_mapping();    
}
