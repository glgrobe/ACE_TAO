// $Id$

#ifndef CIAO_STOCKBROKER_EXEC_H
#define CIAO_STOCKBROKER_EXEC_H

#include /**/ "ace/pre.h"

#include "StockBrokerEC.h"

#include <set>
#include <string>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "StockBroker_exec_export.h"
#include "tao/LocalObject.h"

//namespace CIAO_Stock_StockDistributor_Impl
//namespace CIDL_StockDistributor_Impl
namespace CIAO_Stock_StockBroker_Impl
{

  /**
   * @class StockBroker_exec_i
   *
   * @brief Executor implementation
   *
   * This class implements Stock::StockBroker component
   */
  class STOCKBROKER_EXEC_Export StockBroker_exec_i
    : public virtual StockBroker_Exec,
      public virtual ::CORBA::LocalObject
  {
    public:
    StockBroker_exec_i (void);
    virtual ~StockBroker_exec_i (void);


    // Supported or inherited operations.

    virtual void
    stock_subscribe (const char * stock_name);

    virtual void
    stock_unsubscribe (const char * stock_name);

    // Attribute operations.

    // Port operations.

    virtual void
    push_notify_in (::Stock::StockName *ev);

    // Operations from Components::SessionComponent

    virtual void
    set_session_context (::Components::SessionContext_ptr ctx);

    virtual void configuration_complete ();

    virtual void ccm_activate ();

    virtual void ccm_passivate ();

    virtual void ccm_remove ();

    private:
    ::Stock::CCM_StockBroker_Context_var context_;
    std::set<std::string> subscribed_stock_list_;
  };


  /**
   * @class StockBrokerHome_exec_i
   *
   * @brief Executor implementation
   *
   * This class implements Stock::StockBrokerHome component
   */
  class STOCKBROKER_EXEC_Export StockBrokerHome_exec_i
    : public virtual StockBrokerHome_Exec,
      public virtual ::CORBA::LocalObject
  {
    public:
    StockBrokerHome_exec_i (void);
    virtual ~StockBrokerHome_exec_i (void);

    // Supported or inherited operations.

    // Home operations.

    // Factory and finder operations.

    // Attribute operations.

    // Implicit operations.

    virtual ::Components::EnterpriseComponent_ptr
    create ();
  };


  extern "C" STOCKBROKER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Stock_StockBrokerComp_Impl (void);
  extern "C" STOCKBROKER_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_Stock_StockBrokerHome_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* CIAO_STOCKBROKER_EXEC_H */
