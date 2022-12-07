package com.mymyka.npc;

public abstract class NPCDecorator extends NPC {
    private NPC npc;

    public NPCDecorator(NPC npc) {
        this.npc = npc;
    }

    @Override
    public String getName() {
        return npc.getName();
    }

    @Override
    public void setName(String name) {
        npc.setName(name);
    }

    public void spawn() {
        npc.spawn();
    }
}
