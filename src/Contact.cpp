#include "Contact.h"

void Contact::BeginContact(b2Contact *contact)
{
    auto bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if(bodyUserDataA && bodyUserDataB) 
    {
        auto gameObjectA = static_cast<GameObject *>(bodyUserDataA);
        auto gameObjectB = static_cast<GameObject *>(bodyUserDataB);

        switch (gameObjectA->getBodyType()) 
        {
            case PLAYER:
                playerStartContact(static_cast<Player *>(bodyUserDataA), gameObjectB);
                return;
            case DINO_ENEMY:
            case ROBOT_ENEMY:
                enemyStartContact(static_cast<Enemy *>(bodyUserDataA), gameObjectB);
                return;
            case BULLET:
                bulletStartContact(static_cast<Bullet *>(bodyUserDataA), gameObjectB);
            default:
                break;
        }

        switch (gameObjectB->getBodyType()) 
        {
            case PLAYER:
                playerStartContact(static_cast<Player *>(bodyUserDataB), gameObjectA);
                return;
            case DINO_ENEMY:
            case ROBOT_ENEMY:
                enemyStartContact(static_cast<Enemy *>(bodyUserDataB), gameObjectA);
                return;
            case BULLET:
                bulletStartContact(static_cast<Bullet *>(bodyUserDataB), gameObjectA);

            default:
                break;
        }
    }
}

//-----------------------------------------------
//handle player contacts
void Contact::playerStartContact(Player * player, GameObject * gameObject)
{
    switch (gameObject->getBodyType()) 
    {
        case DINO_ENEMY:
        case ROBOT_ENEMY:
            player->startContact(static_cast<Enemy *>(gameObject));
            break;
        case COIN:
            player->startContact(static_cast<Coin*>(gameObject));
            break;
        case HP_GIFT:
            player->startContact(static_cast<HpGift*>(gameObject));
            break;
        case LIFE_GIFT:
            player->startContact(static_cast<LifeGift*>(gameObject));
            break;
        case BULLET_GIFT:
            player->startContact(static_cast<BulletGift*>(gameObject));
            break;
        case BULLET:
            player->startContact(static_cast<Bullet*>(gameObject));
            break;
        case GATE:
            player->startContact(static_cast<Gate*>(gameObject));
            break;

        default:
            break;
    }
}

//-----------------------------------------------
//hanlde enemy contacts
void Contact::enemyStartContact(Enemy * enemy, GameObject * gameObject) {

    switch (gameObject->getBodyType()) 
    {
        case PLAYER:
            static_cast<Player *>(gameObject)->startContact(enemy);
            break;
        case BULLET:
            enemy->startContact(static_cast<Bullet *>(gameObject));
            break;
    }
}

//-----------------------------------------------
//handle bullet contacts
void Contact::bulletStartContact(Bullet* bullet, GameObject* gameObject)
{
    switch (gameObject->getBodyType()) 
    {
    case WALL:
    case FLOOR:
        bullet->startContact(static_cast<Wall*>(gameObject));
    }
}
