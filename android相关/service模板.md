# service 类模板

## ServiceObserverInterface 接口类
主要定义客户的callback函数


    class ServiceObserverInterface {
     public:
      virtual ~ServiceObserverInterface() = default;
    
      // Called whenever the value of these parameters changes. For |progress|
      // value changes, this method will be called only if it changes significantly.
      virtual void SendStatusUpdate(int64_t last_checked_time,
    double progress,
    update_engine::UpdateStatus status,
    const std::string& new_version,
    int64_t new_size) = 0;
    
      // Called whenever an update attempt is completed.
      virtual void SendPayloadApplicationComplete(ErrorCode error_code) = 0;
    
     protected:
      ServiceObserverInterface() = default;
    };


## android::os::BnUpdateEngine类
继承自IUpdateEngine类， BnUpdateEngine类似乎aidl自动生成的类，是一个模板类

interface IUpdateEngine {
  void applyPayload(String url,
                    in long payload_offset,
                    in long payload_size,
                    in String[] headerKeyValuePairs);
  boolean bind(IUpdateEngineCallback callback);
  void suspend();
  void resume();
  void cancel();
  void resetStatus();
}


## BinderUpdateEngineAndroidService类
 该类继承aidl自动生成的类以及ServiceObserverInterface类


    class BinderUpdateEngineAndroidService : public android::os::BnUpdateEngine,
     public ServiceObserverInterface {
     public:
      BinderUpdateEngineAndroidService(
      ServiceDelegateAndroidInterface* service_delegate);
      ~BinderUpdateEngineAndroidService() override = default;
    
      const char* ServiceName() const {
    return "android.os.UpdateEngineService";
      }
    
      // ServiceObserverInterface overrides.
      void SendStatusUpdate(int64_t last_checked_time,
    double progress,
    update_engine::UpdateStatus status,
    const std::string& new_version,
    int64_t new_size) override;
      void SendPayloadApplicationComplete(ErrorCode error_code) override;

      // android::os::BnUpdateEngine overrides.
      android::binder::Status applyPayload(
      const android::String16& url,
      int64_t payload_offset,
      int64_t payload_size,
      const std::vector<android::String16>& header_kv_pairs) override;
      android::binder::Status bind(
      const android::sp<android::os::IUpdateEngineCallback>& callback,
      bool* return_value) override;
      android::binder::Status suspend() override;
      android::binder::Status resume() override;
      android::binder::Status cancel() override;
      android::binder::Status resetStatus() override;
    
     private:
      // Remove the passed |callback| from the list of registered callbacks. Called
      // whenever the callback object is destroyed.
      void UnbindCallback(android::os::IUpdateEngineCallback* callback);
    
      // List of currently bound callbacks.
      std::vector<android::sp<android::os::IUpdateEngineCallback>> callbacks_;
    
      // Cached copy of the last status update sent. Used to send an initial
      // notification when bind() is called from the client.
      int last_status_{-1};
      double last_progress_{0.0};
    
      ServiceDelegateAndroidInterface* service_delegate_;
    };
    


##  UpdateEngineDaemon类
