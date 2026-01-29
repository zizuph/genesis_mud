object head;
object *body;

void set(object new_head, object *new_body)
{
    head = new_head;
    body = new_body;
}

object query_head(void)       
{
    return head;
}

object *query_body(void)
{
    return body;
}
