// abstract base class
class CBase {
 public:
  virtual void xxx() = 0;
  virtual ~CBase() = default;
};

extern CBase* odr1_create();
extern CBase* odr2_create();
