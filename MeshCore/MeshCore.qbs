import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "MeshCore"
  toRoot: "../../"

  property bool uiSupport: true

  Depends { name: "EksCore" }

  Properties {
    condition: uiSupport

    Depends { name: "Qt.gui" }
    Depends { name: "Qt.widgets" }
  }

  Export {
    Depends { name: "cpp" }
    Depends { name: "EksCore" }

    cpp.includePaths: [ "./include" ]
  }

  Depends {
    name: "ShiftCoreTest"
  }
}
