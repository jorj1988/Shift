import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "MathsCore"
  toRoot: "../../"

  Depends { name: "Qt.core" }
  Depends { name: "ShiftCore" }

  Export {
    Depends { name: "cpp" }
    cpp.includePaths: [ "./include" ]
  }
}
