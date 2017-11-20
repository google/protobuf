// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: unittest_import_proto3.proto
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace Google.Protobuf.TestProtos {

  /// <summary>Holder for reflection information generated from unittest_import_proto3.proto</summary>
  public static partial class UnittestImportProto3Reflection {

    #region Descriptor
    /// <summary>File descriptor for unittest_import_proto3.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static UnittestImportProto3Reflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "Chx1bml0dGVzdF9pbXBvcnRfcHJvdG8zLnByb3RvEhhwcm90b2J1Zl91bml0",
            "dGVzdF9pbXBvcnQaI3VuaXR0ZXN0X2ltcG9ydF9wdWJsaWNfcHJvdG8zLnBy",
            "b3RvIhoKDUltcG9ydE1lc3NhZ2USCQoBZBgBIAEoBSpZCgpJbXBvcnRFbnVt",
            "EhsKF0lNUE9SVF9FTlVNX1VOU1BFQ0lGSUVEEAASDgoKSU1QT1JUX0ZPTxAH",
            "Eg4KCklNUE9SVF9CQVIQCBIOCgpJTVBPUlRfQkFaEAlCPAoYY29tLmdvb2ds",
            "ZS5wcm90b2J1Zi50ZXN0SAH4AQGqAhpHb29nbGUuUHJvdG9idWYuVGVzdFBy",
            "b3Rvc1AAYgZwcm90bzM="));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { global::Google.Protobuf.TestProtos.UnittestImportPublicProto3Reflection.Descriptor, },
          new pbr::GeneratedClrTypeInfo(new[] {typeof(global::Google.Protobuf.TestProtos.ImportEnum), }, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::Google.Protobuf.TestProtos.ImportMessage), global::Google.Protobuf.TestProtos.ImportMessage.Parser, new[]{ "D" }, null, null, null)
          }));
    }
    #endregion

  }
  #region Enums
  public enum ImportEnum {
    [pbr::OriginalName("IMPORT_ENUM_UNSPECIFIED")] Unspecified = 0,
    [pbr::OriginalName("IMPORT_FOO")] ImportFoo = 7,
    [pbr::OriginalName("IMPORT_BAR")] ImportBar = 8,
    [pbr::OriginalName("IMPORT_BAZ")] ImportBaz = 9,
  }

  #endregion

  #region Messages
  public sealed partial class ImportMessage : pb::IMessage<ImportMessage> {
    private static readonly pb::MessageParser<ImportMessage> _parser = new pb::MessageParser<ImportMessage>(() => new ImportMessage());
    private pb::UnknownFieldSet unknownFields = pb::UnknownFieldSet.DefaultInstance;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pb::MessageParser<ImportMessage> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Google.Protobuf.TestProtos.UnittestImportProto3Reflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ImportMessage() {
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        unknownFields = new pb::UnknownFieldSet();
      }
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ImportMessage(ImportMessage other) : this() {
      d_ = other.d_;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ImportMessage Clone() {
      return new ImportMessage(this);
    }

    /// <summary>Field number for the "d" field.</summary>
    public const int DFieldNumber = 1;
    private int d_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public int D {
      get { return d_; }
      set {
        d_ = value;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override bool Equals(object other) {
      return Equals(other as ImportMessage);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public bool Equals(ImportMessage other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (D != other.D) return false;
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        return unknownFields.Equals(other.unknownFields);
      } else {
        return true;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override int GetHashCode() {
      int hash = 1;
      if (D != 0) hash ^= D.GetHashCode();
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        hash ^= unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void WriteTo(pb::CodedOutputStream output) {
      if (D != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(D);
      }
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        unknownFields.WriteTo(output);
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public int CalculateSize() {
      int size = 0;
      if (D != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(D);
      }
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        size += unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(ImportMessage other) {
      if (other == null) {
        return;
      }
      if (other.D != 0) {
        D = other.D;
      }
      if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
        unknownFields.MergeFrom(other.unknownFields);
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(pb::CodedInputStream input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            if (pb::CodedInputStream.GetPreserveUnknownsDefault()) {
              unknownFields.MergeFieldFrom(input);
            } else {
              input.SkipLastField();
            }
            break;
          case 8: {
            D = input.ReadInt32();
            break;
          }
        }
      }
    }

  }

  #endregion

}

#endregion Designer generated code
