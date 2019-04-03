# update_engine android7.12与android8比较

## 对外提供接口变更

android8增加了如下接口


IUpdateEngine.aidl文件

    void SetCohortHint(in String cohort_hint);
    String GetCohortHint();
    int GetEolStatus();

IUpdateEngine.aidl文件

    boolean unbind(IUpdateEngineCallback callback);