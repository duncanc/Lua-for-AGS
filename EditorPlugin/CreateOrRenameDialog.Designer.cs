namespace AGS.Plugin.Lua
{
    partial class CreateOrRenameDialog : System.Windows.Forms.Form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SimpleLuaValueEditor));
            this.ConfirmButton = new System.Windows.Forms.Button();
            this.CancelyButton = new System.Windows.Forms.Button();
            this.NameBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ConfirmButton
            // 
            this.ConfirmButton.Location = new System.Drawing.Point(12, 51);
            this.ConfirmButton.Name = "ConfirmButton";
            this.ConfirmButton.Size = new System.Drawing.Size(94, 39);
            this.ConfirmButton.TabIndex = 0;
            this.ConfirmButton.Text = "Create";
            this.ConfirmButton.UseVisualStyleBackColor = true;
            this.ConfirmButton.Click += new System.EventHandler(this.CreateButton_Click);
            // 
            // CancelyButton
            // 
            this.CancelyButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CancelyButton.Location = new System.Drawing.Point(176, 51);
            this.CancelyButton.Name = "CancelyButton";
            this.CancelyButton.Size = new System.Drawing.Size(96, 39);
            this.CancelyButton.TabIndex = 1;
            this.CancelyButton.Text = "Cancel";
            this.CancelyButton.UseVisualStyleBackColor = true;
            this.CancelyButton.Click += new System.EventHandler(this.CancelButton_Click);
            // 
            // ScriptNameBox
            // 
            this.NameBox.Location = new System.Drawing.Point(12, 25);
            this.NameBox.Name = "ScriptNameBox";
            this.NameBox.Size = new System.Drawing.Size(260, 20);
            this.NameBox.TabIndex = 2;
            this.NameBox.Validating += new System.ComponentModel.CancelEventHandler(this.ScriptNameBox_Validating);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(157, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Enter a name for the new script:";
            // 
            // LuaScriptNameDialog
            // 
            this.AcceptButton = this.ConfirmButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.CancelyButton;
            this.ClientSize = new System.Drawing.Size(284, 100);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.NameBox);
            this.Controls.Add(this.CancelyButton);
            this.Controls.Add(this.ConfirmButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LuaScriptNameDialog";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Add New Lua Script";
            this.Load += new System.EventHandler(this.NewLuaScriptDialog_Load);
            this.Shown += new System.EventHandler(this.NewLuaScriptDialog_Shown);
            this.Activated += new System.EventHandler(this.NewLuaScriptDialog_Activated);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ConfirmButton;
        private System.Windows.Forms.Button CancelyButton;
        private System.Windows.Forms.TextBox NameBox;
        private System.Windows.Forms.Label label1;
    }
}