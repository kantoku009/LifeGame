/**
 * @file    Observer.h
 * @brief   デザインパターン オブザーバーパターン
 */

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <list>
#include <iterator>

/**
 * @brief   オブザーバーパターンにおいて通知を行う場合, 通知したい情報
 * @note    何も定義していないクラス.定義は具象クラスで行う.
 */
class Information
{
};

/**
 * @brief   デザインパターン(オブザーバーパターン) Observer
 *
 */
class Observer
{
public:
    /**
     * @brief   Subjetから通知を受信.
     * @param   Information* i_pcInformation 通知に伴うメッセージ.
     * @return  結果を返す.
     */
    virtual bool update(Information* i_pcInformation=0) = 0;
};



/**
 * @brief   デザインパターン(オブザーバーパターン) Subject
 *
 */
class Subject
{
public:
    Subject(){ }
    virtual ~Subject(){ }

    /**
     * @brief   Observerを登録する.
     * @param   Observer* i_pcObserver 登録するオブザーバ.
     * @return  なし.
     */
    virtual void attach(Observer* i_pcObserver)
    {
        m_pcObserverList.push_back(i_pcObserver);
    }

    /**
     * @brief   Observerを登録解除する.
     * @param   Observer* i_pcObserver 登録解除するオブザーバ.
     * @return  なし.
     */
    virtual void detach(Observer* i_pcObserver)
    {
        std::list<Observer*>::iterator a_Iterator;
        for(a_Iterator=m_pcObserverList.begin(); a_Iterator!=m_pcObserverList.end(); ++a_Iterator)
        {
            if( (*a_Iterator)==i_pcObserver ) m_pcObserverList.erase(a_Iterator);
        }
    }

    /**
     * @brief   Observerを持っているか否かを確認する.
     * @param   i_pcObserver 確認するオブザーバ.
     * @return  引数で渡されたオブザーバを持っているかをどうか返す.
     * @retval  true    持っている.
     * @retval  false   持っていない.
     */
    virtual bool hasObserver(Observer* i_pcObserver)
    {
        std::list<Observer*>::iterator a_Iterator;
        for(a_Iterator=m_pcObserverList.begin(); a_Iterator!=m_pcObserverList.end(); ++a_Iterator)
        {
            if( (*a_Iterator)==i_pcObserver ) return true;
        }

        return false;
    }

protected:
    /**
     * @brief   Observerへ通知を送信.
     * @param   Information* i_pcInformation 通知に伴うメッセージ.
     * @return  なし.
     */
    virtual void notify(Information* i_pcInformation=0)
    {
        bool a_bRet=false;

        std::list<Observer*>::iterator a_Iterator;
        for(a_Iterator=m_pcObserverList.begin(); a_Iterator!=m_pcObserverList.end(); ++a_Iterator)
        {
            a_bRet = (*a_Iterator)->update(i_pcInformation);
        }
    }

    /**
     * @brief   登録されたオブザーバ
     */
    std::list<Observer*> m_pcObserverList;
private:

};

#endif  //__OBSERVER_H__
