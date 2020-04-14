// Used as button first, but the iconAfter is not sticking to the end of the button
// I rather create my own button than totaly tweaking this one
// Leaving binding for reference
[@bs.module "@atlaskit/button"] [@react.component]
external make: (
  ~iconBefore: React.element=?,
  ~iconAfter: React.element=?,
  ~children: React.element=?,
  ~appearance: string=?,
  ~style: ReactDOMRe.Style.t=?
  ) => React.element = "default";

