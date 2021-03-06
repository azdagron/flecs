#include <api.h>

void Clone_empty() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_is_empty(world, e_1));
    test_assert(ecs_is_empty(world, e_2));

    ecs_fini(world);
}

void Clone_empty_w_value() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_is_empty(world, e_1));
    test_assert(ecs_is_empty(world, e_2));

    ecs_fini(world);
}

void Clone_null() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_clone(world, 0, false);
    test_assert(e != 0);

    test_assert(ecs_is_empty(world, e));

    ecs_fini(world);
}

void Clone_null_w_value() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t e = ecs_clone(world, 0, true);
    test_assert(e != 0);

    test_assert(ecs_is_empty(world, e));

    ecs_fini(world);
}

void Clone_1_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_1 = ecs_new(world, Position);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));
    test_assert(ecs_get_ptr(world, e_1, Position) !=  
                ecs_get_ptr(world, e_2, Position));

    ecs_fini(world);
}

void Clone_2_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));
    test_assert(ecs_get_ptr(world, e_1, Position) !=  
                ecs_get_ptr(world, e_2, Position));

    test_assert(ecs_has(world, e_1, Velocity));
    test_assert(ecs_has(world, e_2, Velocity));
    test_assert(ecs_get_ptr(world, e_1, Velocity) !=  
                ecs_get_ptr(world, e_2, Velocity));

    ecs_fini(world);
}

void Clone_3_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_TYPE(world, Type, Position, Velocity, Mass);

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));
    test_assert(ecs_get_ptr(world, e_1, Position) !=  
                ecs_get_ptr(world, e_2, Position));

    test_assert(ecs_has(world, e_1, Velocity));
    test_assert(ecs_has(world, e_2, Velocity));
    test_assert(ecs_get_ptr(world, e_1, Velocity) !=  
                ecs_get_ptr(world, e_2, Velocity));

    test_assert(ecs_has(world, e_1, Mass));
    test_assert(ecs_has(world, e_2, Mass));
    test_assert(ecs_get_ptr(world, e_1, Mass) !=  
                ecs_get_ptr(world, e_2, Mass));

    ecs_fini(world);
}

void Clone_1_component_w_value() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_set(world, e_1, Position, {10, 20});

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    test_assert(p_1 != NULL);
    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    test_assert(p_2 != NULL);
    test_assert(p_1 != p_2);
    test_int(p_2->x, 10);
    test_int(p_2->y, 20);

    ecs_fini(world);
}

void Clone_2_component_w_value() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_set(world, e_1, Position, {10, 20});
    ecs_set(world, e_1, Velocity, {30, 40});

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));
    test_assert(ecs_has(world, e_1, Velocity));
    test_assert(ecs_has(world, e_2, Velocity));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    test_assert(p_1 != NULL);
    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    test_assert(p_2 != NULL);
    test_assert(p_1 != p_2);
    test_int(p_2->x, 10);
    test_int(p_2->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v_1 != NULL);
    test_int(v_1->x, 30);
    test_int(v_1->y, 40);

    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);
    test_int(v_2->x, 30);
    test_int(v_2->y, 40);

    ecs_fini(world);
}

void Clone_3_component_w_value() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_set(world, e_1, Position, {10, 20});
    ecs_set(world, e_1, Velocity, {30, 40});
    ecs_set(world, e_1, Mass, {50});

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));
    test_assert(ecs_has(world, e_1, Velocity));
    test_assert(ecs_has(world, e_2, Velocity));
    test_assert(ecs_has(world, e_1, Mass));
    test_assert(ecs_has(world, e_2, Mass));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    test_assert(p_1 != NULL);
    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    test_assert(p_2 != NULL);
    test_assert(p_1 != p_2);
    test_int(p_2->x, 10);
    test_int(p_2->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v_1 != NULL);
    test_int(v_1->x, 30);
    test_int(v_1->y, 40);

    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);
    test_int(v_2->x, 30);
    test_int(v_2->y, 40);

    Mass *m_1 = ecs_get_ptr(world, e_1, Mass);
    test_assert(m_1 != NULL);
    test_int(*m_1, 50);

    Mass *m_2 = ecs_get_ptr(world, e_2, Mass);
    test_assert(m_2 != NULL);
    test_assert(m_1 != m_2);
    test_int(*m_2, 50);

    ecs_fini(world);
}

void Clone_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e_1 = ecs_new(world, Tag);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Tag));
    test_assert(ecs_has(world, e_2, Tag));

    ecs_fini(world);
}

void Clone_tag_w_value() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t e_1 = ecs_new(world, Tag);
    test_assert(e_1 != 0);

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Tag));
    test_assert(ecs_has(world, e_2, Tag));

    ecs_fini(world);
}

void Clone_1_tag_1_component() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, e_1, Position, Tag);

    ecs_set(world, e_1, Position, {10, 20});

    ecs_entity_t e_2 = ecs_clone(world, e_1, false);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Tag));
    test_assert(ecs_has(world, e_2, Tag));

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));

    ecs_fini(world);
}

void Clone_1_tag_1_component_w_value() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, e_1, Position, Tag);

    ecs_set(world, e_1, Position, {10, 20});

    ecs_entity_t e_2 = ecs_clone(world, e_1, true);
    test_assert(e_2 != 0);
    test_assert(e_1 != e_2);

    test_assert(ecs_has(world, e_1, Tag));
    test_assert(ecs_has(world, e_2, Tag));

    test_assert(ecs_has(world, e_1, Position));
    test_assert(ecs_has(world, e_2, Position));

    Position *p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}
