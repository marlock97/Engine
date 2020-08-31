#include <string>
#include "src/Core/DataTypes.h"
#include "src/Core/Rtti.h"

namespace Engine
{
  class IBase
  {
  public:
    static const Rtti TYPE;
    virtual const Rtti& getType() const;

    bool isExactly(const Rtti& otherType) const;
    bool isDerived(const Rtti& otherType) const;
    bool isExactly(const IBase& otherType) const;
    bool isDerived(const IBase& otherType) const;

    std::string getName() const;
    void setName();
    u32 getUID() const;

  private:
    std::string name_;
    u32 UID_ = 0;

  protected:
    IBase();
    virtual ~IBase() = 0;
  };
}